<?php
 $code = rand(999999, 111111);
 echo "$code";
			 $subject = "Email Verification Code";
            $message = "Your verification code is $code";
            $sender = "From: prmaratha96k@gmail.com";
            mail('prgayake@mitaoe.ac.in', $subject, $message, $sender)


?>