#ifndef _CORE_H
#define _CORE_H
#define core Core::GetInstance()
#define net core.GetNetwork()
#define log core.GetLogFile()
class Core
{
private:
	Core();
	Core( const Core & ) {};
	~Core();
	Network* network;
	FILE* logFile;
public:
	static Core & GetInstance()
	{
		static Core singletone;
		return singletone;
	};

	void StartServer();
	FILE* GetLogFile() { return this->logFile;};
	Network* GetNetwork() { return this->network;};
};
#endif