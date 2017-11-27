#ifndef _NETWORK_H
#define _NETWORK_H
#define SIGNAL(event_name, stream, priority, reliability) \
	net->GetRPC()->Signal(event_name, stream, priority, reliability, 0, net->GetServerAddr(), false, false)
class Network
{
private:
	RakPeerInterface* peer;
	RPC4* rpc4;
	SystemAddress serverAddress;
	bool isConnected;
	bool isInitialized;
public:
	Network();
	~Network();
	bool Initialize();
	bool IsInitialized(){return this->isInitialized;};
	void Disconnect(bool isForced);
	bool Connect(string address, unsigned short port);
	void ReceivePackets();
	RakPeerInterface* GetPeer() { return this->peer;};
	RPC4* GetRPC(){ return this->rpc4;};
	void RegisterRPCFuncs();
	void SetServerAddress(SystemAddress sa);
	SystemAddress GetServerAddr(){ return this->serverAddress;};
	bool IsConnected(){ return this->isConnected;}; //Inform is server address exist
};
#endif