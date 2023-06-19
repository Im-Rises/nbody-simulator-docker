import express from 'express'
import redis from 'redis'
import bodyParser from 'body-parser'

const app = express()
const PORT = process.env.PORT || 9000
const REDIS_PORT = process.env.REDIS_PORT || 6379
const redisPort = REDIS_PORT.replace(/^tcp:/, 'redis:');
const client = redis.createClient(redisPort)
const totalparticules = process.env.NB_PARTICULES || 1000

var valueFuture = 0
var currentFrame = 0
var nbParticulesCalculated = 0

var switched = false

client.on('connect', () => console.log(`Redis is connected on port ${redisPort}`))
client.on("error", (error) => console.error(error))

app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json({ limit: '100mb' }));

//Obtenir une seule particule (pas utile pour nous)
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

//Obtenir les particules du présent
//Si les particules n'ont pas été update, wasUpdated vaut false, sinon true
//Si wasUpdated vaut true, il faut mettre à jour les particules du futur
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
            particules: [],
            wasUpdated: false
          })
        }

        client.mget(keysPresent, (err, values) => {
          if (err) {
            console.error(err);
            return;
          }
          var s = switched
          switched = false
          if(s)
          {
            currentFrame++;
          }
          //console.log(values.length)
          //console.log(JSON.stringify(values).length)
          return res.status(200).send({
            message: `Retrieved all particules' data`,
            particules: values,
            wasUpdated: s
          })
        })
      }
    })
  } catch (error) {
    console.log(error)
  }
})

app.get('/all/particules/', (req, res) => {
  try {
    client.keys('*', async (err, keys) => {
      if (err) {
        console.error(err);
        return;
      }

      if (keys) 
      {
        const keysPresent = keys.filter(key => (key % 2) === valueFuture)

        if(keysPresent.length === 0)
        {

          return res.status(200).send({
            message: `No particules in present`,
            particules: [],
            wasUpdated: false
          })
        }

        client.mget(keysPresent, (err, values) => {
          if (err) {
            console.error(err);
            return;
          }
          //console.log(values)
          for(let i = 0; i < values.length; i++)
          {
            let val = JSON.parse(values[i])
            if(valueFuture === 0)
            {
              val.index = val.index / 2;
            }
            else
            {
              val.index = (val.index - 1) / 2;
            }
            values[i] = JSON.stringify(val)

          }
          //console.log(values.length)
          //console.log(values)
          //console.log(JSON.stringify(values).length)
          return res.status(200).send({
            message: `Retrieved all particules' data`,
            particules: values,
          })
        })
      }
    })
  } catch (error) {
    console.log(error)
  }
})

//Obtenir les particules du futur (normalement ce n'est pas utile)
app.get('/all/future/', (req, res) => {
  try {
    //console.log("test")
    client.keys('*', async (err, keys) => {
      if (err) {
        console.error(err);
        return;
      }

      if (keys) 
      {
        const keysFuture = keys.filter(key => (key % 2) === ((valueFuture + 1) % 2) )


        if(keysFuture.length === 0)
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


function switchParticules()
{
  valueFuture = (valueFuture + 1) % 2
  switched = true
}


//Obtenir la frame actuelle
app.get('/getFrame/', (req, res) => {
  try {
    return res.status(200).send({
      message: `got frame`,
      frame: currentFrame
    })
  } catch (error) {
    console.log(error)
  }
})
    

//Mettre à jour des particules
app.post('/api/', (req, res) => {
  try {
    //console.log(req.body.particules)
    const particules = req.body.particules
    particules.forEach(particule => {
      if(valueFuture === 0)
      {
        particule.index = particule.index * 2 + 1;
      }
      else
      {
        particule.index = particule.index * 2;
      }
      //console.log(particule.index);
      client.setex(particule.index, 1440, JSON.stringify(particule))
    })
    nbParticulesCalculated += particules.length
    if(nbParticulesCalculated >= totalparticules)
    {
      switchParticules()
    }
    const particuleLog = JSON.stringify(particules)
    return res.status(200).send({
      particule: particuleLog
    })
  } catch (error) {
    console.log(error)
  }
})


app.listen(PORT, () => console.log(`Server running on port ${PORT}`))