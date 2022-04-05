// Load the AWS SDK for JS
var AWS = require("aws-sdk");

// Set a region to interact with (make sure it's the same as the region of your table)
AWS.config.update({region: 'ap-south-1'});



// Create the Service interface for DynamoDB
var dynamodb = new AWS.DynamoDB({apiVersion: '2012-08-10'});

// Create the Document Client interface for DynamoDB
var ddbDocumentClient = new AWS.DynamoDB.DocumentClient();

async function scanForResults(){
    try {
        var params = {
            TableName: "Library"
        };
        var result = await dynamodb.scan(params).promise()
        console.log(result)
    } catch (error) {
        console.error(error);
    }
}
scanForResults()