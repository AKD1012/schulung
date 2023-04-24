#include <variant>
#include <map>

class VplDataSet
{
	private:
		std::vector<std::variant<std::map<VPLK, std::vector<VPLP>>, std::vector<VPLG>>> vplData_;

    public:
		VplDataSet();
		void setData(std::variant<std::pair<VPLK, VPLP>, VPLG> vplData);
        void printData();
};

class OrderDataSet 
{
	private: 
		std::map<AUSK, std::map<AUSP, VplDataSet>> orderData_;

	public:
		void fillDataSet(std::vector<OrderData> orderData);
		void printData(); 	
};