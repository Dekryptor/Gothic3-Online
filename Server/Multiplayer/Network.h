#ifndef _NETWORK_H
#define _NETWORK_H
#define SIGNAL(event_name, stream, priority, address) \
	net->GetRPC()->Signal(event_name, stream, priority, RELIABLE, 0, address, false, false)
#define SIGNAL_ALL_PLAYERS(event_name, stream, priority) \
		for( playerListIter i = pM.playerList.begin(); i != pM.playerList.end(); ++i ) \
			SIGNAL(event_name, stream, priority, i->second->address)
class Network
{
private:
	RakPeerInterface* peer;
	RPC4* rpc4;
	size_t maxSlots;
public:
	Network();
	~Network();

	bool InitializeAndStart(size_t maxConnections, unsigned short port);
	void ReceivePackets();
	RPC4* GetRPC() { return this->rpc4;};
	RakPeerInterface* GetPeer() { return this->peer;};
	void RegisterRPCFuncs();
	inline size_t GetMaxSlots( void ){ return this->maxSlots;};
};
#endif