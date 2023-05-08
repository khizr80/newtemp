#include"User.h"

using namespace System::Data::SqlClient;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
public ref class admin : public User
{
public:
	String^ complain;
	String^ revenue;
	bool login(String^ i, String^ pass)
	{

		String^ id = i;
		String^ password = pass;

		if (id->Length == 0 || password->Length == 0) {
			MessageBox::Show("Please enter email and password", "Email or Password Empty", MessageBoxButtons::OK);
			return 0;
		}

		try {
			String^ connString = rr;
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "SELECT * FROM [admin] WHERE id=@no AND password=@pwd";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@no", id);
			command.Parameters->AddWithValue("@pwd", password);
			SqlDataReader^ reader = command.ExecuteReader();
			if (reader->Read()) {

				this->id = reader->GetString(0);
				password = reader->GetString(1);
				/*first_name = reader->GetString(2);
				last_name = reader->GetString(3);
				revenue = reader->GetString(4);
				security_q = reader->GetString(5);
				age = reader->GetString(6);
				phone_no = reader->GetString(7);*/
				return 1;
				//MessageBox::Show("" + user->first_name + user->last_name + user->id + user->password + user->insurance_no
					//+ user->security_q + user->age + user->phone_no + user->role, "message", MessageBoxButtons::OK);
			}
			else {
				MessageBox::Show("Email or password is incorrect",
					"Email or Password Error", MessageBoxButtons::OK);
				return 0;
			}
		}
		catch (Exception^ e) {
			MessageBox::Show("Failed to connect to database", "Database Connection Error", MessageBoxButtons::OK);
			return 0;
		}
	}
	void forget_passowrd(String^ i, String^ q)
	{
		try
		{
			id = i;
			security_q = q;
			String^ connString = rr;
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "SELECT password FROM [admin] WHERE id=@id AND security_q=@security_q";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@id", id);
			command.Parameters->AddWithValue("@security_q", security_q);
			SqlDataReader^ reader = command.ExecuteReader();
			String^ password;
			if (reader->Read()) {
				password = reader->GetString(0);
			}
			MessageBox::Show("your password is \n" + password, "your password ", MessageBoxButtons::OK);
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Id or security question incorrect", "Forget password Failure", MessageBoxButtons::OK);
		}
	}

};