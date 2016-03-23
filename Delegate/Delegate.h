#ifndef DELEGATE_H
#define DELEGATE_H value

#include <algorithm>
#include <functional>
#include <string>

namespace ultimate {
	template<typename R, typename... Params>
	class Delegate {
	
	public:
		//set the function
		void set(std::function<R(Params...)> func) {
			m_function = func;
		}

		//run the function
		template <class... Args>
		R run(Args&&... args) {
			return m_function(std::forward<Args>(args)...);
		}

		//setter for tag, to be used with delegate list
		void setTag(std::string tag){
			m_tag = tag;
		}

		//getter for tags, to be used with delegate list
		std::string getTag(){
			return m_tag;
		}

	private:
		std::function<R(Params...)> m_function;
		std::string m_tag;
	};
} 

#endif