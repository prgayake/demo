const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const path = require('path');
// Load the AWS SDK for Node.js
var AWS = require('aws-sdk');
// Set the region 
AWS.config.update({
    region: 'ap-south-1'
});

// Create an SQS service object
var sqs = new AWS.SQS({
    apiVersion: '2012-11-05'
});


app.use(bodyParser.urlencoded({
    extended: true
}));
app.use(bodyParser.json());
//setting Public directory
const publicDirectory = path.join(__dirname, './public');
app.use(express.static(publicDirectory));

app.use(bodyParser.urlencoded({
    extended: true
}));
app.use(bodyParser.json());

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');


app.get('/', (req, res) => {
    res.render('index');
});
app.get('/form', (req, res) => { //get request

    res.render('form');
});

app.post('/sendData', (req, res) => {
    console.log(req.body);

    var params = {
        // Remove DelaySeconds parameter and value for FIFO queues
        DelaySeconds: 10,
        MessageAttributes: {
            "BookName": {
                DataType: "String",
                StringValue: req.body.bookname
            },
            "BookId": {
                DataType: "String",
                StringValue: req.body.bookid
            },
            "Auther": {
                DataType: "String",
                StringValue: req.body.auther
            },
            "bookissueto": {
                DataType: "String",
                StringValue: req.body.bookissueto
            },
            "studentid": {
                DataType: "String",
                StringValue: req.body.studentid
            },
            "issuedate": {
                DataType: "String",
                StringValue: req.body.issuedate
            },
            "duedate": {
                DataType: "String",
                StringValue: req.body.duedate
            }
        },
        MessageBody: "Information about current NY Times fiction bestseller for week of 12/11/2016.",
        // MessageDeduplicationId: "TheWhistler",  // Required for FIFO queues
        // MessageGroupId: "Group1",  // Required for FIFO queues
        QueueUrl: "https://sqs.ap-south-1.amazonaws.com/304089859339/myqueue"
    };

    sqs.sendMessage(params, function (err, data) {
        if (err) {
            console.log("Error", err);
        } else {
            console.log("Success", data.MessageId);
        }
    });

});

app.listen(3000, () => {
    console.log('Server started on port 3000');
});