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


// Create the Service interface for DynamoDB
var dynamodb = new AWS.DynamoDB({apiVersion: '2012-08-10'});

// Create the Document Client interface for DynamoDB
var ddbDocumentClient = new AWS.DynamoDB.DocumentClient();
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
        DelaySeconds: 1,
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

app.get('/table', (req, res) => {
    
    var sqs = new AWS.SQS({ apiVersion: "2012-11-05" });
    var docClient = new AWS.DynamoDB.DocumentClient();
    var queueURL = "https://sqs.ap-south-1.amazonaws.com/304089859339/myqueue";
    
var params = {
    AttributeNames: ["SentTimestamp"],
    MaxNumberOfMessages: 10,
    MessageAttributeNames: ["All"],
    QueueUrl: queueURL,
    VisibilityTimeout: 20,
    WaitTimeSeconds: 0,
  };
  
  sqs.receiveMessage(params, function (err, data) {
    if (err) {
      console.log("Receive Error", err);
    } else if (data.Messages) {
  
      console.log("Received Messages", data.Messages);
  
      var table = "Library";
  
  
      var params1 = {
        TableName:table,
        Item:{
           "BookId":data.Messages[0].MessageAttributes.BookName.StringValue,
            "BookName":data.Messages[0].MessageAttributes.BookName.StringValue,
            "Auther":data.Messages[0].MessageAttributes.Auther.StringValue,
            "BookIssueTo":data.Messages[0].MessageAttributes.bookissueto.StringValue,
            "StudentId":data.Messages[0].MessageAttributes.studentid.StringValue,
            "IssueDate":data.Messages[0].MessageAttributes.issuedate.StringValue,
            "Duedate":data.Messages[0].MessageAttributes.duedate.StringValue,
  
        }
    };
  
      console.log("Adding a new item...");
      docClient.put(params1, function (err, data) {
        if (err) {
          console.error(
            "Unable to add item. Error JSON:",
            JSON.stringify(err, null, 2)
          );
        } else {
          console.log("Added item:", JSON.stringify(data, null, 2));
        }
      });
  
      var deleteParams = {
        QueueUrl: queueURL,
        ReceiptHandle: data.Messages[0].ReceiptHandle,
      };
      sqs.deleteMessage(deleteParams, function (err, data) {
        if (err) {
          console.log("Delete Error", err);
        } else {
          console.log("Message Deleted", data);
        }
      });
    }
  });
    async function scanForResults(){
        try {
            var params = {
                TableName: "Library"
            };
            var result = await dynamodb.scan(params).promise()
            // console.log(result.Items[0].BookId.S)
            res.render('table', {data: result.Items});
        } catch (error) {
            console.error(error);
        }
    }
    scanForResults()
});

app.listen(3000, () => {
    console.log('Server started on port 3000');
});