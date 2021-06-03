const nModule = require('bindings')('main');
const express = require('express');
const path = require('path');


const fibonacci = new nModule.NanFibonacci();
const app = express();
const port = 3000

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

app.get('/fibonacci', (req, res) => {
    const result = fibonacci.get();
    if (result[0] === '-'){
        res.send({
            fibonacci: 'infinity'
        })
    }
    else{
        res.send({
            fibonacci: result
        })
    }

});

app.listen(port, () => console.log(`http://localhost:${port}/`));

