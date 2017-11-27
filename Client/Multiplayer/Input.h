#ifndef _INPUT_H
#define _INPUT_H
#define inp Input::GetInstance()
class Input
{
private:
	Input();
	Input( const Input & );
	~Input();
public:
	static Input & GetInstance()
	{
		static Input singletone;
		return singletone;
	}
private:
	bool isGameInputActive;
	char keyBuffer;
public:
	bool IsGameInputActive() { return this->isGameInputActive; };
	void SetGameInputActive(bool enable);
	void Process();
	SHORT KeyPressed(int vKey);
	char GetLastChar();
	void OnKeyInput(char Key); //CB
};
#endif 