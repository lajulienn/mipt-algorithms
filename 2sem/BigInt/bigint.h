#include <vector>
#include <string>

class BigInt {
public:
	BigInt() : sign_(1) {}
	explicit BigInt(int value) : sign_(1), digits_(1, value) { if (value < 0) sign_ = -1; }

	int get_sign() const { return sign_; }

	void scan(); // get data from cin and initialize digits_ and sign
	void print() const;

	void shift();

	bool operator<(const BigInt &n) const;
	bool operator==(const BigInt &n) const;
	BigInt operator*(int value);
	BigInt operator+(const BigInt &n2);
	BigInt operator-(const BigInt &n2);
	BigInt operator*(const BigInt &n2);
	//friend std::string operator/(const BigInt &n1, const BigInt &n2);

	friend int cmp(const BigInt &n1, const BigInt &n2);
	friend void scan(BigInt &n1, BigInt &n2);
private:
	int sign_;
	std::vector<int> digits_;
};

//std::string operator/(const BigInt &n1, const BigInt &n2);

void scan(BigInt &n1, BigInt &n2);
int cmp(const BigInt &n1, const BigInt &n2);

