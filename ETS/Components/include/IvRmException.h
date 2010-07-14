#pragma once
//--------------------------------------------------------------------------------------------------------//
namespace IvRmCore
{
	namespace IvRmException
	{
		//--------------------------------------------------------------------------------------------------------//
		class AbstractException
		{
		public:

			struct ExceptionData
			{
				typedef boost::shared_ptr<ExceptionData>	pointer;
				pointer			__source;
				std::string		__description;

				ExceptionData(std::string description, pointer source = pointer())
				{
					__description	= description;
					__source		= source;
				};

				virtual std::string toString() const
				{
					return ((bool)__source) ? __source->toString() + "\n" + __description : __description;
				};

				virtual std::string getDescription() const
				{
					return __description;
				};

				~ExceptionData()
				{
				};
			};

			ExceptionData::pointer data;

			AbstractException(const AbstractException& rmexception){
				data = rmexception.data;
			};

			AbstractException(std::string description)
			{
				if (!(bool)data)
					data = ExceptionData::pointer(new ExceptionData(description));
			};

			AbstractException(std::string description, const AbstractException& source)
			{
				if (!(bool)data)
					data = ExceptionData::pointer(new ExceptionData(description, source.data));
			};

			virtual ~AbstractException() 
			{
			};

			virtual std::string toString() const
			{
				return ((bool)data) ? data->toString() : "";
			};

			std::string getDescription() const
			{
				return ((bool)data) ? data->getDescription() : "";
			};
		};
		//--------------------------------------------------------------------------------------------------------//
		class NoContractPrice: public AbstractException
		{
		public:
			NoContractPrice(std::string description)
				:AbstractException(description)
			{
			};

			NoContractPrice(std::string description, const AbstractException& source)
				:AbstractException(description, source)
			{
			};

			virtual ~NoContractPrice() 
			{
			};
		};
		//--------------------------------------------------------------------------------------------------------//
		class NoContractGreeksCalculated: public AbstractException
		{
		public:
			NoContractGreeksCalculated(std::string description)
				:AbstractException(description)
			{
			};

			NoContractGreeksCalculated(std::string description, const AbstractException& source)
				:AbstractException(description, source)
			{
			};

			virtual ~NoContractGreeksCalculated() 
			{
			};
		};
		//--------------------------------------------------------------------------------------------------------//
		class NoContractVolatilityCalculated: public AbstractException
		{
		public:
			NoContractVolatilityCalculated(std::string description)
				:AbstractException(description)
			{
			};

			NoContractVolatilityCalculated(std::string description, const AbstractException& source)
				:AbstractException(description, source)
			{
			};

			virtual ~NoContractVolatilityCalculated() 
			{
			};
		};
		//--------------------------------------------------------------------------------------------------------//
		class NoContractTheoreticalVolatility: public AbstractException
		{
		public:
			NoContractTheoreticalVolatility(std::string description)
				:AbstractException(description)
			{
			};

			NoContractTheoreticalVolatility(std::string description, const AbstractException& source)
				:AbstractException(description, source)
			{
			};

			virtual ~NoContractTheoreticalVolatility() 
			{
			};
		};
		//--------------------------------------------------------------------------------------------------------//
		class ContractNotCalculated: public AbstractException
		{
		public:
			ContractNotCalculated(std::string description)
				:AbstractException(description)
			{
			};

			ContractNotCalculated(std::string description, const AbstractException& source)
				:AbstractException(description, source)
			{
			};

			virtual ~ContractNotCalculated() 
			{
			};
		};
	};
};
//--------------------------------------------------------------------------------------------------------//