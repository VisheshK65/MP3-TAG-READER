#ifndef INFO_H
#define INFO_H

//enum to hold the success and failure  
typedef enum
{
	m_success,
	m_failure
}Status;

//enum used to access the operation option selected by the user 
typedef enum 
{
	m_help,
	m_view,
	m_edit,
	m_unsupport
}OperationType;

//enum used to access the which tag label is been accessed during the view option
typedef enum
{
	m_tit2,
	m_tpe1,
	m_talb,
	m_tyer,
	m_tcon,
	m_tcom
}TagReader;

//enum used to access which tag label which is been accessed during the edit option
typedef enum
{
	e_tit2,
	e_tpe1,
	e_talb,
	e_tyer,
	e_tcon,
	e_tcom,
	e_unsupport
}TagReaderEdit;

OperationType check_operation(char *argv[]); //function to find which operation has been selected by the user 
#endif

