#ifndef _CHAT_H
#define _CHAT_H
#define chat Chat::GetInstance()
struct chatLine
{
	string text;
	unsigned char color[4];
};
class Chat
{
private:
	Chat();
	Chat(const Chat &) {};
	~Chat();
public:
	static Chat & GetInstance()
	{
		static Chat singletone;
		return singletone;
	}
private:
	size_t maxLines;
	vector<chatLine> chatLines;
	bool visible;
	bool inputOpened;
	string inputText;
	int cursorPos;
public:
	void draw();
	void addLine(string text, unsigned char r, unsigned char g, unsigned char b);
	bool isVisible(){ return this->visible;};
	void setVisible(bool enable) { this->visible = enable;};
	void showInput(bool enable);
	bool isInputVisible() { return this->inputOpened;};
	void drawInput();
	void onChar(char* symbol);
	void clear() { this->chatLines.clear();};

};
#endif