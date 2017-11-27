<?php
	$approved_groups = array(4, 8, 3);
	$login = "";
	$password = "";
	$login = htmlspecialchars($_GET["name"]);
	$password = htmlspecialchars($_GET["password"]);
	$sql = mysql_connect("localhost", "root", "lol1997xD")
		or die("0");
	mysql_select_db("g3_mybb") or die("0");
	$query = "SELECT * FROM `bb_users` WHERE `username` = '$login'";
	$array = mysql_query($query)
		or die("0");
	$array = mysql_fetch_array($array);
	//var_dump($array);
	if($array['password'] == $password)
	{
		foreach($approved_groups as $value)
		{
			if($value == $array['usergroup'])
			{
				echo("1");
				goto end;
			}
		}
		die("0");
	}
	else
	{		
		die("0");
	}
	end:
	mysql_free_result($array);
	mysql_close($sql);
?>