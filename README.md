# Password_Manager
A simple console‑based password manager written in C++ that allows users to securely store, retrieve, and delete credentials. It includes a master password system, random password generation, file storage, and a clean menu interface.

Mater Password feature: 
- User must set a master password on first launch
- All future access requires authentication
- Prevents unauthorized access to stored credentials

Credential Management: 
- Add a username with an automatically generated secure password
- Retrieve stored passwords
- Delete credentials
- All changes are saved automatically

File storage: 
- Credentials are saved in password.dat
- Automatically loads saved credentials on startup
