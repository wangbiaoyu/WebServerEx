#pragma once

namespace common
{

template <class T>
class ISingleton{

public:
	explicit ISingleton();
	~ISingleton();
	ISingleton(const ISingleton& ) =  delete;
	ISingleton& operator=(const ISingleton& ) = delete;
	static ISingleton* GetInstance(){
		if(singleton_ == NULL)
			singleton_ =  new ISingleton();
		return singleton_;
	}

private:
	static ISingleton* singleton_;	

};

singleton = new ISingleton();
}
