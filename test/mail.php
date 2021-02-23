<?php

require 'PHPMailerAutoload.php';



$mail = new PHPMailer;

//$mail->SMTPDebug = 4;                               // Enable verbose debug output

$mail->isSMTP();                                      // Set mailer to use SMTP
$mail->Host = 'smtp.gmail.com;';  // Specify main and backup SMTP servers
$mail->SMTPAuth = true;                               // Enable SMTP authentication
$mail->Username = 'prmaratha96k@gmail.com';                 // SMTP username
$mail->Password = 'pradyumna@9';                           // SMTP password
$mail->SMTPSecure = 'tls';                            // Enable TLS encryption, `ssl` also accepted
$mail->Port = 587;                                    // TCP port to connect to 

$mail->setFrom('prmaratha96k@gmail.com', 'Pradyumna Gayake');
$mail->addAddress($Email);     // Add a recipient


   // Optional name
$mail->isHTML(true);                                  // Set email format to HTML

$mail->Subject = 'Booking Confirmation ';
$mail->Body    = "Dear".$F_name. "Your Order is confirmed ! Visit Website for more details  ";
$mail->AltBody = 'Thanks Regards : Virtuals Hotels :)  ';

if(!$mail->send()) {
    echo 'Message could not be sent.';
    echo 'Mailer Error: ' . $mail->ErrorInfo;
} else {
    echo 'Message has been sent';
}