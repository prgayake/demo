// Load the AWS SDK for Node.js
var AWS = require("aws-sdk");
// Set the region
AWS.config.update({
  region: "ap-south-1",
});

// Create an SQS service object
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