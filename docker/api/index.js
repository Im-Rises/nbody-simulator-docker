import express from 'express'
import redis from 'redis'
import bodyParser from 'body-parser'

const app = express()
const PORT = process.env.PORT || 9000
const REDIS_PORT = process.env.REDIS_PORT || 6379
const client = redis.createClient(REDIS_PORT)

var valueFuture = 0

client.on('connect', () => console.log(`Redis is connected on port ${REDIS_PORT}`))
client.on("error", (error) => console.error(error))

app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json({ limit: '100mb' }));

app.get('/api/:particuleIndex', (req, res) => {
  try {
    const particuleIndex = req.params.particuleIndex
    client.get(particuleIndex, async (err, data) => {
      if (data) {
        return res.status(200).send({
          message: `Retrieved particule ${particuleIndex}'s data`,
          particule: JSON.parse(data)
        })
      }
    })
  } catch (error) {
    console.log(error)
  }
})

app.get('/all/present/', (req, res) => {
  try {
    client.keys('*', async (err, keys) => {
      if (err) {
        console.error(err);
        return;
      }

      if (keys) 
      {
        const keysPresent = keys.filter(key => key % 2 == valueFuture)

        if(keysPresent.length == 0)
        {

          return res.status(200).send({
            message: `No particules in present`,
            particules: []
          })
        }

        client.mget(keysPresent, (err, values) => {
          if (err) {
            console.error(err);
            return;
          }
          //console.log(values.length)
          //console.log(JSON.stringify(values).length)
          return res.status(200).send({
            message: `Retrieved all particules' data`,
            particules: values
          })
        })
      }
    })
  } catch (error) {
    console.log(error)
  }
})

app.get('/all/future/', (req, res) => {
  try {
    console.log("test")
    client.keys('*', async (err, keys) => {
      if (err) {
        console.error(err);
        return;
      }

      if (keys) 
      {
        const keysFuture = keys.filter(key => key % 2 == ((valueFuture + 1) % 2) )


        if(keysFuture.length == 0)
        {
          return res.status(200).send({
            message: `No particules in present`,
            particules: []
          })
        }

        client.mget(keysFuture, (err, values) => {
          if (err) {
            console.error(err);
            return;
          }
    

          return res.status(200).send({
            message: `Retrieved all particules' data`,
            particules: values
          })
        })
      }
    })
  } catch (error) {
    console.log(error)
  }
})

app.post('/switch/', (req, res) => {
  try {
    valueFuture = (valueFuture + 1) % 2
    return res.status(200).send({
      message: `Switched present and future`,
    })
  } catch (error) {
    console.log(error)
  }
})


app.post('/api/', (req, res) => {
  try {
    //console.log(req.body)
    const particules = req.body.particules
    particules.forEach(particule => {
      client.setex(particule.index, 1440, JSON.stringify(particule))
    })
    const particuleLog = JSON.stringify(particules)
    return res.status(200).send({
      particule: particuleLog
    })
  } catch (error) {
    console.log(error)
  }
})

app.listen(PORT, () => console.log(`Server running on port ${PORT}`))