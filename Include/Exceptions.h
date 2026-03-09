/**
 *  Exceptions.h
 *  Custom exception classes for game error handling.
 *
 * Defines exceptions for unknown collisions, resource loading errors,
 * file errors, and missing resources. Each exception provides a descriptive message.
 */
#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "GameObject.h"

class UnknownCollisionException : public std::exception
{
public:

	UnknownCollisionException(const GameObject& obj1, const GameObject& obj2)
		: m_errorMsg(std::string("\nUnknown collision between: ") + typeid(obj1).name() +
			" " + typeid(obj2).name()) {
	}

	const char* what() const noexcept
	{
		return m_errorMsg.c_str();
	}

private:
	std::string m_errorMsg;
};

class ResourceLoadException : public std::exception
{
public:
	explicit ResourceLoadException(const std::string& message)
		: m_errorMsg("Resource load error: " + message) {}

	const char* what() const noexcept {
		return m_errorMsg.c_str();
	}

private:
	std::string m_errorMsg;
};

class FileIOException : public std::exception
{
public:
	explicit FileIOException(const std::string& message)
		: m_errorMsg("File I/O error: " + message) {}

	const char* what() const noexcept {
		return m_errorMsg.c_str();
	}

private:
	std::string m_errorMsg;
};

class ResourceNotFoundException : public std::exception
{
public:
	explicit ResourceNotFoundException(const std::string& message)
		: m_errorMsg("Resource not found: " + message) {}

	const char* what() const noexcept {
		return m_errorMsg.c_str();
	}

private:
	std::string m_errorMsg;
};
