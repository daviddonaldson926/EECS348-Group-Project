const express = require('express');
const childProcess = require('child_process');

const app = express();
const port = 3000;

app.use(express.json());

// Handle requests to the root URL
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});

app.post('/process', (req, res) => {
    const inputData = req.body.input;

    // Run the C++ program as a child process
    const child = childProcess.spawn('./parser.exe');

    // Send input to the C++ program
    child.stdin.write(inputData);
    child.stdin.end();

    let result = '';

    // Receive output from the C++ program
    child.stdout.on('data', (data) => {
        result += data.toString();
    });

    child.stderr.on('data', (data) => {
        console.error(`Error: ${data}`);
    });

    // Handle the end of the process
    child.on('close', (code) => {
        console.log(`Child process exited with code ${code}`);
        res.send(result);
    });
});

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});