#ifndef NEXUS_ENGINE__SCRIPTCOMPONENT_HPP_
#define NEXUS_ENGINE__SCRIPTCOMPONENT_HPP_

# include "../EntityInfos.hpp"

namespace nx
{
	namespace env
	{
		class ScriptComponent
		{
		private:
			EntityInfos		_entityInfos;
			std::string		_scriptPath;

		public:
			ScriptComponent(std::string const& _name)
				: _entityInfos(_name) {}
			ScriptComponent(std::string const& _name, std::string const& scriptPath)
				: _entityInfos(_name), _scriptPath(scriptPath) {}
			~ScriptComponent() {}

			// Setters
			void		setScriptPath(const std::string& scriptPath)
			{
				this->_scriptPath = scriptPath;
				_entityInfos.setIsModified(true);
			}

			// Getters
			const std::string& 	getScriptPath()
			{
				return (this->_scriptPath);
			}

		public:
			const EntityInfos&			getEntityInfos() const
			{
				return (this->_entityInfos);
			}

			EntityInfos&			getEntityInfos()
			{
				return (this->_entityInfos);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__SCRIPTCOMPONENT_HPP_ */