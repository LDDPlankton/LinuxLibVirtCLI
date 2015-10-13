#ifndef VIRTUALIZATION_H_
#define VIRTUALIZATION_H_

class Virtualization
{
public:
	Virtualization() { }
	virtual ~Virtualization() { }
	virtual std::string getErrorMessage() = 0;
	virtual bool createVM(const char *xmlconfig) = 0;
	virtual bool deleteVM(std::string vmname) = 0;
	virtual bool startVM(std::string vmname) = 0;
	virtual bool stopVM(std::string vmname) = 0;

protected:
};

#endif
