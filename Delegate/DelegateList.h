#ifndef DELEGATE_LIST
#define DELEGATE_LIST

#include "Delegate.h"
#include <vector>
#include <string>

namespace ultimate{
	template<typename R, typename... Params>
	class DelegateList{
	public:
		//adds a delegate to the list
		void add(Delegate<R, Params...> dlg, std::string tag){
			dlg.setTag(tag);
			dlgList.push_back(dlg);
		}

		//removes all delegate with the given tag
		void removeWithTag(std::string tag){
			for (unsigned int i = 0; i < dlgList.size(); i++)
				if (dlgList[i].getTag() == tag){
					dlgList.erase(dlgList.begin()+i);
					i--;
				}
		}

		//runs all the delegates in the list
		void runAll(){
			for (Delegate<R, Params...> dlg : dlgList)
				dlg.run();
		}

		//only runs delegate with the given tag
		void runWithTag(std::string tag){
			for (Delegate<R, Params...> dlg : dlgList)
				if (dlg.getTag() == tag)
					dlg.run();
		}

		//clears the delegate list
		void clear(){
			dlgList.clear();
		}

	private:
		std::vector<Delegate<R, Params...>> dlgList;
	};
}

#endif