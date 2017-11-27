#ifndef _CORE_H
#define _CORE_H
#define core Core::GetInstance()
#define net core.GetNetwork()
class Network;
class Core
{
private:
	Core();
	Core( const Core & ){};
public:
	~Core();

	static Core & GetInstance()
	{
		static Core singletone;
		return singletone;
	}
	void StartGame();
	void Process();
	bool IsStarted() { return this->isStarted;};
	Network* GetNetwork(){ return this->pNetwork;};
	bool Auth(const char* login, const char* password);
private:
	bool isStarted;
	Network* pNetwork;
};
#endif