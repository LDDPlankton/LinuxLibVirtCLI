#ifndef KVM_H_
#define KVM_H_

#include <iostream>
#include <fstream>
#include <map>
#include "../ConfigLoader/XMLLoader.h"
#include "Helpers/MiscTool.h"
#include <libvirt/libvirt.h>
#include "../Virtualization/Virtualization.h"
using namespace std;

class KVM : Virtualization
{
public:
	KVM()
	{
		this->error_message = "";
		this->conn = NULL;
		this->dom = NULL;
	}

	~KVM()
	{
		if(this->dom != NULL)
			virDomainFree(this->dom);
		if(this->conn != NULL)
			virConnectClose(this->conn);
	}

	/*
	 * This function will attempt to connect to determine if our qemu system is running
	 *
	 * @return bool
	 */
	bool connect()
	{
		this->conn = virConnectOpen("qemu:///system");
	    if (this->conn == NULL)
	    {
	    	this->error_message = "Cannot connect to qemu:///system!";
	    	return false;
	    }
	    return true;
	}

	std::string getErrorMessage()
	{
		return this->error_message;
	}

	/*
	 * This function calls the LibVirt API to define config for our VPS
	 *
	 * @param const char* xmlconfig
	 * @return bool
	 */
	bool defineVM(const char *xmlconfig)
	{
	    this->dom = virDomainDefineXML(this->conn, xmlconfig);
	    if(!dom)
	    {
	    	this->error_message = "Failed to define new Guest!";
	    	return false;
	    }
	    return true;
	}

	/*
	 * This function will attempt to use the LibVirt API to remove a VPS's config
	 *
	 * @param virDomainPtr ptr_dom
	 * @return bool
	 */
	bool undefineVM(virDomainPtr ptr_dom)
	{
	    int n = virDomainUndefine(ptr_dom);
	    if(n == -1)
	    {
	    	this->error_message = "Failed to undefine Guest!";
	    	return false;
	    }
	    return true;
	}

	bool createVM(const char *xmlconfig)
	{
		//DEFINE OR RETURN FALSE
		if(!defineVM(xmlconfig))
			return false;
		return true;
	}

	/*
	 * This function is a primary function, and is how our system will attempt to delete a VM
	 *
	 * @param string vmname
	 * @return bool
	 */
	bool deleteVM(std::string vmname)
	{
		/*
		if(!this->xml.loadXMLFile(vmname))
		{
			this->error_message = xml.getErrorMessage();
			return false;
		}
		std::string xml_content = xml.getXMLContent();
		*/
		int pid = fork();
		int status;
		if(pid == 0)
		{
			close(2);	//CLOSE STDERR
			this->dom = virDomainLookupByName(this->conn, vmname.c_str());
		}
		else
		{
			wait(&status);
			exit(1);
		}

		if(this->dom == NULL)
		{
			this->error_message = "Not able to lookup domain [" + vmname + "]";
			return false;
		}
		//UNDEFINE CHECK
		if(!this->undefineVM(this->dom))
			return false;

		return true;
	}

	/*
	 * This function is the primary method our system will use to start a VM
	 *
	 * @param string vmname
	 * @return bool
	 */
	bool startVM(std::string vmname)
	{
		this->dom = virDomainLookupByName(this->conn, vmname.c_str());
		if(this->dom == NULL)
		{
			this->error_message = "Not able to lookup domain [" + vmname + "]";
			return false;
		}

	    if(virDomainCreate(this->dom) == -1)
	    {
	    	this->error_message = "Failed to boot guest!";
	    	return false;
	    }
	    return true;
	}

	/*
	 * This function will stop a running VM
	 *
	 * @param string vmname
	 * @return bool
	 */
	bool stopVM(std::string vmname)
	{
		int pid = fork();
		int status;
		if(pid == 0)
		{
			close(2);	//CLOSE STDERR
			this->dom = virDomainLookupByName(this->conn, vmname.c_str());
		}
		else
		{
			wait(&status);
			exit(1);
		}

		if(this->dom == NULL)
		{
			this->error_message = "Not able to lookup domain [" + vmname + "]";
			return false;
		}

	    if(virDomainDestroy(this->dom) == -1)
	    {
	    	this->error_message = "Failed to shutdown guest!";
	    	return false;
	    }

		return true;
	}

private:
	virConnectPtr conn;
	virDomainPtr dom;
	std::string error_message;
	XMLLoader xml;
};

#endif
