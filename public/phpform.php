<!DOCTYPE HTML>
<html>
<head>
<title>Php form</title>
</head>
<body>

<?php
$name = $email = "";
var_dump($_POST);
var_dump($HTTP_RAW_POST_DATA);
?>

<form method="post">
  Name: <input type="text" name="name" value="<?php echo $name;?>">
  <br><br>
  E-mail: <input type="text" name="email" value="<?php echo $email;?>">
  <br><br>
  <input type="submit" name="submit">
</form>

<?php
  echo "Name: " . $_POST['name'] . ", Email: " . $_POST['email'] . "<br/>";
?>
</body>
</html>