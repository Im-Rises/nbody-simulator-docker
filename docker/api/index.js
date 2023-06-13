const express = require('express')
const redis = require('redis')
const bodyParser = require('body-parser')
const app = express()
const PORT = process.env.PORT || 9000
const REDIS_PORT = process.env.REDIS_PORT || 6379
const client = redis.createClient(REDIS_PORT)

client.on('connect', () => console.log(`Redis is connected on port ${REDIS_PORT}`))
client.on("error", (error) => console.error(error))

app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());

app.get('/api/:particuleIndex', (req, res) => {
  try {
    const particuleIndex = req.params.particuleIndex
    client.get(particuleIndex, async (err, data) => {
      if (data) {
        console.log(data)
        return res.status(200).send({
          message: `Retrieved particule ${particuleIndex}'s data`,
          particule: JSON.parse(data)
        })
      }/*else {
        const particule = `{"particuleIndex": ${particuleIndex}, "x": 0}`
        client.setex(particuleIndex, 1440, particule)
        return res.status(200).send({
          message: `Create particule ${particuleIndex}'s data to the server`,
          particule: particule
        })
      }*/
    })
  } catch (error) {
    console.log(error)
  }
})

app.post('/api/', (req, res) => {
  try {
    console.log(req.body)
    const particuleBody = req.body
    const particuleIndex = particuleBody.particuleIndex
    const particule = JSON.stringify(particuleBody)
    client.setex(particuleIndex, 1440, particule)
    return res.status(200).send({
      message: `Create particule ${particuleIndex}'s data to the server`,
      particule: particule
    })
  } catch (error) {
    console.log(error)
  }
})

app.listen(PORT, () => console.log(`Server running on port ${PORT}`))

module.exports = app