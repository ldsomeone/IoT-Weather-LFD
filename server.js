if (process.env.NODE_ENV !== 'production') {
    require('dotenv').config()
}

const port = 6900  //declares a variable called port with a value of 6900
const express = require('express') // Imports the Express.js framework
const expressLayouts = require('express-ejs-layouts') // Imports the Express.js EJS layouts
const app = express() // Creates an instance of Express.js


// set and use things
app.set('view engine', 'ejs')  // Sets the view engine to EJS.
app.set('views', __dirname + '/views') // This sets the directory for the ejs templates to views
app.set('layout', 'layouts/layout')  // Sets the layout template
app.use(expressLayouts)  // Uses the EJS layout middleware
app.use(express.static('public')) // Serves static files from the 'public' directory
app.use(express.json({ limit: '1mb' })) // incoming JSON data parsed with a size limit of 1mb.

// Routes
const indexRouter = require('./routes/index') // Defines route handlers for various paths, that will render the EJS templates.

// The below lines of code define route handlers for various paths (/about, /links...), rendering EJS templates.
app.get('/about', (req, res) => {
    res.render('about'); // reders the "about.ejs" that is located in the views directory
});

app.get('/underdevelopment', (req, res) => {
    res.render('underdevelopment'); //reders the "underdevelopment.ejs" that is located in the views directory
});

app.get('/links', (req, res) => {
    res.render('externallinks'); // reders the "externallinks.ejs" that is located in the views directory (folder)
});


app.use('/', indexRouter) //the index router is at the root path of / (the home page)


// Starts the Express server on the specified port of 6900
app.listen(process.env.PORT || port, () => {
    console.log('Web App ready at http://localhost:' + port)  // Will log a message to indicate that the web app is ready
})

