#pragma once
namespace Utils
{
	class AnyValue
	{
	public:
		class placeholder
		{
		public:
			placeholder() {}
			virtual ~placeholder() {}
			virtual placeholder* clone() const = 0;
		};

		template<class t>
		class holder
			: public placeholder
		{
		public:
			holder(const t& value)
				: content(value)
			{
			}

			~holder()
			{
			}

			placeholder* clone() const
			{
				return new holder<t>(content);
			}

			t content;
		};

		AnyValue()
			: _content(0)
		{
		}

		AnyValue(const AnyValue& other_)
			: _content(other_._content ? other_._content->clone() : nullptr)
		{
		}

		template<class t>
		AnyValue(const t& value_)
			: _content(new holder<t>(value_))
		{
		}

		~AnyValue()
		{
			delete _content;
		}


		template<class t>
		operator t () const
		{
			return dynamic_cast<holder<t>*>(_content)->content;
		}

		AnyValue& operator = (const AnyValue& right_)
		{
			if (this->_content != nullptr)
			{
				delete this->_content;
				this->_content = nullptr;
			}

			if (right_._content != nullptr)
			{
				this->_content = right_._content->clone();
			}

			return *this;
		}
	private:
		placeholder* _content;
	};
}