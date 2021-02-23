<?php

 include('connect.php');
  require 'PHPMailerAutoload.php';



  		 if(isset($_POST['checkmail']))
  		 {	
  		 	$Email= $_POST['Email'];
  		 	$code =rand(99999,11111);
  		 	$check_email = "SELECT * FROM userdetails WHERE Email='$Email'";
  		 	$result =mysqli_query($conn,$check_email);
  		 	if(mysqli_num_rows($result)>0)
  		 	{
  		 		$code = rand(999999, 111111);
  		 		$insert_code = "UPDATE userdetails SET code = $code WHERE Email='$Email'";
            	$result1 =mysqli_query($conn,$insert_code);
            	if($result1)
            	{
            		mailer($Email,$code);	
            		
            	}
            	else
            	{
            		echo "could not sent mail";
            	}

            
  		 	}
  		 	else
  		 	{
  		 		echo "mail not found";
  		 	}
  		 	
  		 }



  		 	

  		 	function mailer($Email,$code){

						$mail = new PHPMailer;

						//$mail->SMTPDebug = 4;                               // Enable verbose debug output

						$mail->isSMTP();                                      
						$mail->Host = 'smtp.gmail.com;';  
						$mail->SMTPAuth = true;                               
						$mail->Username = 'prmaratha96k@gmail.com';                 
						$mail->Password = 'pradyumna@9';                           
						$mail->SMTPSecure = 'tls';                            
						$mail->Port = 587;                                     

						$mail->setFrom('prmaratha96k@gmail.com', 'Pradyumna Gayake');
						$mail->addAddress($Email);     

						$mail->isHTML(true);                                  // Set email format to HTML

						$mail->Subject = 'Password Reset Code';
						$mail->Body    = "Your password reset code is $code
											<!DOCTYPE html>
											 <html>
											 <head>
											 	<title></title>
											 </head>
											 <body>
											 <br>
											 <br>
											 <h4>Thanks Regards : Virtuals Hotels :) </h4>
											 </body>
											 </html> ";

						if(!$mail->send()) {
						    echo 'Message could not be sent.';
						    echo 'Mailer Error: ' . $mail->ErrorInfo;
						} else {
						    echo 'Message has been sent';
						}
  		 	}

?>