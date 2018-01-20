#ifndef NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_
# define NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>

namespace nx {
	class NetworkServerFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		NetworkServerFrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~NetworkServerFrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}

		// Framework Methods (must be virtual pure)
		virtual void pingNetworkServerFramework() = 0;

	};	
}

#endif /* NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_*/