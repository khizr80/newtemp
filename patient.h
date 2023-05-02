#include"User.h"

using namespace System::Data::SqlClient;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Globalization;
public ref class Patient : public User
{
public:
	String^ insurance_no;
	bool login(String^ i, String^ pass)
	{
		
		String^ id = i;
		String^ password = pass;

		if (id->Length == 0 || password->Length == 0) {
			MessageBox::Show("Please enter email and password","Email or Password Empty", MessageBoxButtons::OK);
			return 0;
		}
		try 
		{
			String^ connString = rr;
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "SELECT * FROM [user] WHERE id=@no AND password=@pwd";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@no", id);
			command.Parameters->AddWithValue("@pwd", password);
			SqlDataReader^ reader = command.ExecuteReader();
			if (reader->Read()) 
			{
				this->id = reader->GetString(0);
				 this->password = reader->GetString(1);
				 first_name = reader->GetString(2);
				 last_name = reader->GetString(3);
				 insurance_no = reader->GetString(4);
				 security_q = reader->GetString(5);
				 age = reader->GetString(6);
				 phone_no = reader->GetString(7);
				 return 1;
				//MessageBox::Show("" + user->first_name + user->last_name + user->id + user->password + user->insurance_no
					//+ user->security_q + user->age + user->phone_no + user->role, "message", MessageBoxButtons::OK);
			}
			else {
				MessageBox::Show("Email or password is incorrect","Email or Password Error", MessageBoxButtons::OK);
				return 0;
			}
		}
		catch (Exception^ e) {
			MessageBox::Show("Failed to connect to database", "Database Connection Error", MessageBoxButtons::OK);
			return 0;
		}
	}
	void signup(String^i, String^ p, String^ f, String^ l, String^ in, String^ se, String^ a, String^ ph, String^ con)
	{
		id = i;
		password = p;
		first_name = f;
		last_name = l;
		insurance_no = in;
		security_q = se;
		age = a;
		phone_no = ph;
		confirm_password = con;
		if (first_name->Length == 0 || last_name->Length == 0 || phone_no->Length == 0 || id->Length == 0
			|| password->Length == 0 || insurance_no->Length == 0 || age->Length == 0 || confirm_password->Length == 0)
		{

			MessageBox::Show("Please enter all the fields", "On or more empty fields", MessageBoxButtons::OK);
			return;
		}
		if (String::Compare(password, confirm_password) != 0) {
			MessageBox::Show("Password and Confirm Password do not match", "Password Error", MessageBoxButtons::OK);
			return;
		}
		try {
			String^ connString = rr;
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "INSERT INTO [user] (first_name, last_name, id, insurance_no, age, phone_no, password,security_q) VALUES (@first_name, @last_name, @id, @insurance_no, @age, @phone_no, @password,@security_q)";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@id", id);
			command.Parameters->AddWithValue("@first_name", first_name);
			command.Parameters->AddWithValue("@last_name", last_name);
			command.Parameters->AddWithValue("@insurance_no", insurance_no);
			command.Parameters->AddWithValue("@age", age);
			command.Parameters->AddWithValue("@phone_no", phone_no);
			command.Parameters->AddWithValue("@password", password);
			command.Parameters->AddWithValue("@security_q", security_q);
			command.ExecuteNonQuery();
			
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Failed to register new user", "Register Failure", MessageBoxButtons::OK);
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
			String^ sqlQuery = "SELECT password FROM [user] WHERE id=@id AND security_q=@security_q";
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
	void change_detail(String^ f, String^ l, String^ i, String^ p, String^ in, String^ se, String^ a, String^ ph)
	{
		if (f->Length == 0 || l->Length == 0 || i->Length == 0 || p->Length == 0
			|| in->Length == 0 || se->Length == 0 || ph->Length == 0)
		{
			MessageBox::Show("Please enter all the fields", "One or more empty fields", MessageBoxButtons::OK);
			return;
		}
		id = i;
		password = p;
		first_name = f;
		last_name = l;
		insurance_no = in;
		security_q = se;
		phone_no = ph;
		age = a;
		try {
			String^ connString = rr;
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "UPDATE [user] SET first_name = @first_name, last_name = @last_name, insurance_no = @insurance_no, age = @age, phone_no = @phone_no, password = @password, security_q = @security_q WHERE id = @id";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@id", id);
			command.Parameters->AddWithValue("@first_name", first_name);
			command.Parameters->AddWithValue("@last_name", last_name);
			command.Parameters->AddWithValue("@insurance_no", insurance_no);
			command.Parameters->AddWithValue("@age", age);
			command.Parameters->AddWithValue("@phone_no", phone_no);
			command.Parameters->AddWithValue("@password", password);
			command.Parameters->AddWithValue("@security_q", security_q);
			command.ExecuteNonQuery();
			MessageBox::Show("changed successfully", "change information", MessageBoxButtons::OK);
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Failed to register new user", "Register Failure", MessageBoxButtons::OK);
		}
	}
	void make_appointment(DateTime^ date, String^ doctor_id, String^ iid, String^ doc_name)
	{
		try {
			String^ connString = rr;
			SqlConnection sqlConn(connString);
			sqlConn.Open();

			// Check if patient already has an appointment with the same doctor on the given date
			String^ sqlCountQuery = "SELECT COUNT(*) FROM [appointment] WHERE date = @date AND patient_id = @id AND doctor_id = @doc_id;";
			SqlCommand countCommand(sqlCountQuery, % sqlConn);
			countCommand.Parameters->AddWithValue("@date", date);
			countCommand.Parameters->AddWithValue("@id", iid);
			countCommand.Parameters->AddWithValue("@doc_id", doctor_id);
			int appointmentCount = (int)countCommand.ExecuteScalar();

			if (appointmentCount >= 1)
			{
				MessageBox::Show("Failed to make appointment", "Patient already has an appointment with the same doctor on the given date", MessageBoxButtons::OK);
				return;
			}

			// Check if the doctor already has 3 appointments on the given date
			sqlCountQuery = "SELECT COUNT(*) FROM [appointment] WHERE date = @date AND doctor_id = @doc_id;";
			countCommand.CommandText = sqlCountQuery;
			countCommand.Parameters->Clear();
			countCommand.Parameters->AddWithValue("@date", date);
			countCommand.Parameters->AddWithValue("@doc_id", doctor_id);
			appointmentCount = (int)countCommand.ExecuteScalar();

			if (appointmentCount >= 3)
			{
				MessageBox::Show("Failed to make appointment", "Appointment limit reached for the given doctor on the given date", MessageBoxButtons::OK);
				return;
			}

			// Insert the appointment
			String^ sqlInsertQuery = "INSERT INTO [appointment] (doctor_id, patient_id, date, doctor_name) VALUES (@doc_id, @id, @date, @doc_name);";
			SqlCommand insertCommand(sqlInsertQuery, % sqlConn);
			insertCommand.Parameters->AddWithValue("@doc_id", doctor_id);
			insertCommand.Parameters->AddWithValue("@id", iid);
			insertCommand.Parameters->AddWithValue("@date", date);
			insertCommand.Parameters->AddWithValue("@doc_name", doc_name);
			insertCommand.ExecuteNonQuery();

			MessageBox::Show("Success", "Appointment book", MessageBoxButtons::OK);
		}
		catch (Exception^ e) {
			MessageBox::Show("Failed to connect to database", "Database Connection Error", MessageBoxButtons::OK);
		}
	}
	void cancel_appointment(String^ selectedOption)
	{
		try
		{
			String^ connString = rr;
			SqlConnection sqlConn(connString);

			// Extracting values from input string
			String^ doctorName;
			String^ doctorId;
			String^ date;
			bool isDoctorNameComplete = false;
			bool isDoctorIdComplete = false;
			int l = selectedOption->Length;
			for (int i = 0;i < l;i++)
			{
				if (selectedOption[i] == ':')
				{
					isDoctorNameComplete = true;
				}
				else if (isDoctorNameComplete == true && selectedOption[i] != ' ')
				{
					doctorName += selectedOption[i];
				}
				else if (selectedOption[i] == ' '&& isDoctorNameComplete == true)
				{
					break;
				}
			}
			isDoctorNameComplete = false;
			for (int i = 0;i < l;i++)
			{
				if (selectedOption[i] == ';')
				{
					isDoctorNameComplete = true;
				}
				else if (isDoctorNameComplete == true&&selectedOption[i] == ' ')
				{
					break;
				}
				else if (isDoctorNameComplete == true && selectedOption[i] != ' ')
				{
					doctorId += selectedOption[i];
				}
			}
			isDoctorNameComplete = false;
			for (int i = 0;i < l;i++)
			{
				if (selectedOption[i] == ',')
				{
					isDoctorNameComplete = true;
				}
				else if (isDoctorNameComplete == true && selectedOption[i] == ' ')
				{
					break;
				}
				else if (isDoctorNameComplete == true && selectedOption[i] != ' ')
				{
					date += selectedOption[i];
				}
			}
			DateTime dat = DateTime::ParseExact(date, "yyyy-MM-dd", CultureInfo::InvariantCulture);

			sqlConn.Open();
			String^ sqlQuery = "DELETE FROM [appointment] WHERE doctor_id=@doc_id AND patient_id=@pat_id AND date=@date";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@doc_id", doctorId);
			command.Parameters->AddWithValue("@pat_id", getid());
			command.Parameters->AddWithValue("@date", dat);
			int rowsAffected = command.ExecuteNonQuery();
			if (rowsAffected > 0)
			{
				MessageBox::Show("Success", "Cancel Appointment", MessageBoxButtons::OK);
			}
			else
			{
				MessageBox::Show("Failed to connect to database", "Database Connection Error", MessageBoxButtons::OK);
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Failed to connect to database", "Database Connection Error", MessageBoxButtons::OK);
		}
	}

		String^ getid()
	{
		return id;
	}
};