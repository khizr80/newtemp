#pragma once

using namespace System::Data::SqlClient;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

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
	String^ script;
	String^ scriptAdd;
	String^ rr = "Data Source=I-MAC\\SQLEXPRESS;Initial Catalog=mono;Integrated Security=True";
	void complain(String^ x)
	{
		try {
			String^ connString = rr;
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "INSERT INTO [complain] (complain) VALUES (@complain)";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@complain", x);
			command.ExecuteNonQuery();
			MessageBox::Show("Success", "Complain enter", MessageBoxButtons::OK);
		}
		catch (Exception^ e) {
			MessageBox::Show("Failed to connect to database", "Database Connection Error", MessageBoxButtons::OK);

		}
	}

};
