#ifndef NEXUS_ENGINE__ENGINE_CORE_HPP_
#define NEXUS_ENGINE__ENGINE_CORE_HPP_

# define BOOST_ALL_DYN_LINK

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Nexus/standalone/external/any.hpp"

#include "Nexus/modules/maths/maths.hpp"
#include "Nexus/modules/physics/physics.hpp"
#include "Nexus/modules/xml/Parser.hpp"
#include "Nexus/modules/environment/Environment.hpp"

#include "Nexus/systems/SystemTpl.hpp"

#include "Nexus/standalone/GameInfosParser/GameInfosParser.hpp"
#include "Nexus/standalone/thread/ScopedLock.hpp"
#include "Nexus/standalone/network/netutils.hpp"

#include "Nexus/errors/RunWithoutSetupException.hpp"
#include "Nexus/errors/SystemNotFoundException.hpp"

#include "Nexus/rendering.hpp"
#include "Nexus/script.hpp"
#include "Nexus/networkclient.hpp"
#include "Nexus/networkserver.hpp"

struct UdpEventPacket {
	UdpEventPacket() {}
	UdpEventPacket(const nx::EVENT type, const nx::Any& object) : type_(type), object_(object) {}
	UdpEventPacket(const UdpEventPacket& other) : type_(other.type_), object_(other.object_) {}

	nx::EVENT type_;
	nx::Any object_;

	template <typename Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar & type_;
		ar & object_;
	}
};

namespace nx {
  class Engine {
  private:
		static nx::Engine						_instance;
  public:
		static nx::Engine& 						Instance();

  public:
		static nx::UdpEventPacket deserialize(const std::string& data) {
			nx::UdpEventPacket packet;
			std::stringstream archive_stream(data);
			{
				boost::archive::text_iarchive archive(archive_stream);
				archive >> packet;
			}

			return packet;
		}

		static std::string serialize(const nx::UdpEventPacket& packet) {
			std::stringstream ss;
			{
				boost::archive::text_oarchive archive(ss);
				archive << packet;
			}
			return ss.str();
		}

  private:
		bool											_run;
		bool											_debug;
		std::vector<std::shared_ptr<nx::SystemTpl>>		_systems;
		bool 											_serverOnly;
		nx::env::Environment 							_env;

	private:
		Engine(const bool debug = false);
		virtual ~Engine ();

  public:
		bool  ping(void) const;

  private:
		bool checkEngineIntegrity(void) const;

  public:
	  void emit(const nx::EVENT type, const external::any& data)
	  {
		  this->emit(nx::Event(type, data));
	  }

	  void emit(const nx::Event& event)
	  {
		  nx::Log::inform("New event catched in the Engine: {" + std::to_string(event.type) + "}");
		  std::for_each(
			  this->_systems.begin(),
			  this->_systems.end(),
			  [&](const auto system) {
			  	system->emitter(event);
		  	}
		  );
	  }

		template<typename T>
		static T* cast(const std::shared_ptr<nx::SystemTpl>& src)
		{
			auto ptr = src.get();
			if (!ptr) return nullptr;
			return dynamic_cast<T*>(ptr);
		}

  public:
		void startup(bool serverOnly = false);
		void setup(const std::string& confPath, bool serverOnly);
		void stop(void);
		int run(const std::function<void(void)>&);
		void coreLoop(const std::function<void(void)>& userCallback);

  private:
		void _fixedUpdate();
		void _update();
		void _lateUpdate();
		void _render();

  public:
		bool isSetup(void) const;
		const bool isServer(void) const;
		bool debug(void) const;
		void setDebugFlag(const bool);
		const std::vector<std::shared_ptr<nx::SystemTpl>>& getSystems(void) const;
		const std::shared_ptr<nx::SystemTpl>& getSystemByName(const std::string&) const;
		const nx::env::Environment& getEnv() const { return this->_env; }
		nx::env::Environment& getEnv() { return this->_env; }
  };
} /* nx */

#endif
