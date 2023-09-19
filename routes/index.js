const express = require('express') // Imports the Express.js framework
const router = express.Router()  // Creates an instance of an Express.js router
const {fetch} = require('undici')  // Imports the 'fetch' function from the 'undici' library

// Defines a route handler for the root path ('/')
router.get('/', async(req, res) => {
    try {
        const data = await getApiData()   // Calls the 'getApiData' function to fetch API data asynchronously
        res.render('index', {obj: data} )  // Renders the 'index.ejs' template with the fetched data as an object
    } catch (error) {
        console.error('Error:', error);   // Logs an error if there is a problem with fetching data
        res.status(500).send('An error occurred while fetching data.');  // Sends a internal server error if an error (instead of rendering the webpage)
    }
})

// Async function to fetch API data (that is sent from the esp-32/arduino code)
async function getApiData() {
    try { 
        const res = await fetch('http://192.168.1.140') // Fetches data from the specified URL (with our unique ip adress)

        if (!res.ok) {
            throw new Error('Failed to fetch data')  // Throws an error if the response status is not okay
        }

        const txt = await res.json()  // Parses the JSON response body


        // Constructs a 'data' object with specific properties from the JSON data.
        const data = {
            sensName : txt.name,
            location : txt.variables.location,
            id: txt.id,
            hardware: txt.hardware,
            percentageOfMaxCapacity : txt.variables.percentageOfMaxCapacity,
            temperature : txt.variables.temperature,
            humidity : txt.variables.humidity,
        }

        console.log(txt) // Logs the parsed JSON data to the console.
        return data; // Returns the constructed 'data' object

    } catch (error) {
        console.error('Error:', error)  // Logs an error if there is a problem with fetching or processing data
        throw error  // Throws the error to propagate it up the call stack
    }
    
}

module.exports = router // Exports the Express router for use in other parts of the application