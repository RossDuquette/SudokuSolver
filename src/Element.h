class Element
{
	private:
		int number;
		int count;
		bool possible[10];
		
	public:
		Element();
		Element(int num);		
		void setNum(int num);
		int getNum();
		bool getKnown();
		bool setFalse(int n);
		bool getPossible(int n);
		bool canGuess();
};
