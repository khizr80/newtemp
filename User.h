#pragma once

using namespace System::Data::SqlClient;
using namespace System;

public ref class User {
public:
	String^ id;
	String^ password;
	String^ first_name;
	String^ last_name;
	String^ phone_no;
	String^ security_q;
	String^ confirm_password;
	String^ age;
	String^ rr = "Data Source=DESKTOP-9T5F2B3;Initial Catalog=mono;Integrated Security=True";
	bool complain(String^ x)
	{
		try {

			String^ connString = rr;
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "INSERT INTO [complain] (complain) VALUES (@complain)";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@complain", x);
			command.ExecuteNonQuery();
			
			return 1;
		}
		catch (Exception^ e) {
			return 0;
		}
	}
};
