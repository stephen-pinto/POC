#ifndef __DDF_PROVIDER_COLLECTION_TYPES_HEADER
#define __DDF_PROVIDER_COLLECTION_TYPES_HEADER
#pragma once

#include <objbase.h>
#include <iostream>

template <typename T>
struct NODE
{
	T data;
	NODE* next;
	NODE* previous;
};

//template <typename T>
//typedef NODE<T>* PNODE<T>;

template <typename T>
class TypedDataCollection
{

private:

	NODE<T>* root_node = NULL;
	NODE<T>* tail_node = NULL;

	NODE<T>* CreateNewNode()
	{
		NODE<T>* new_node = new NODE<T>();
		//new_node->data = NULL;
		new_node->next = NULL;
		new_node->previous = NULL;
		return new_node;
	}

	void Remove(NODE<T>* node)
	{
		if (node == NULL)
			return;

		NODE<T>* temp_node = NULL;
		
		if (node == root_node && node != tail_node)
		{
			node->next->previous = NULL;
			root_node = node->next;
		}
		else if (node != root_node && node != tail_node)
		{
			temp_node = node->previous;
			temp_node->next = node->next;
			node->next->previous = temp_node;
		}
		else if (node == tail_node && node != root_node)
		{
			node->previous->next = NULL;
			tail_node = node->previous;
		}

		delete(node);
		this->Count--;
	}

public:

	int Count = 0;

	void Add(T data)
	{
		NODE<T>* new_node = this->CreateNewNode();
		new_node->data = data;

		if (this->root_node == NULL)
		{
			root_node = tail_node = new_node;
		}
		else
		{
			tail_node->next = new_node;
			new_node->previous = tail_node;
			tail_node = new_node;
		}
		this->Count++;
	}

	void Remove(T data)
	{
		NODE<T>* temp_node = NULL;
		for (temp_node = this->root_node; temp_node != NULL; temp_node = temp_node->next)
		{
			if (temp_node->data == data)
				break;
		}

		if (temp_node == NULL)
			return;

		NODE<T>* temp_node = NULL;

		if (node == root_node && node != tail_node)
		{
			node->next->previous = NULL;
			root_node = node->next;
		}
		else if (node != root_node && node != tail_node)
		{
			temp_node = node->previous;
			temp_node->next = node->next;
			node->next->previous = temp_node;
		}
		else if (node == tail_node && node != root_node)
		{
			node->previous->next = NULL;
			tail_node = node->previous;
		}

		delete(temp_node);
		this->Count--;
	}

	int ContainsNode(T data)
	{
		for (int indx = 0, NODE<T>* temp_node = this->root_node; temp_node != NULL; temp_node = temp_node->next, indx++)
		{
			if (temp_node->data == data)
				return indx;
		}
		return -1;
	}

	void RemoveAt(int index)
	{
		int indx;
		NODE<T>* temp_node = NULL;
		for (indx = 0, temp_node = this->root_node; temp_node != NULL && indx != index; temp_node = temp_node->next, indx++);
		if (temp_node != NULL)
			Remove(temp_node);
	}

	T ElementAt(int index)
	{
		int indx;
		NODE<T>* temp_node = NULL;
		for (indx = 0, temp_node = this->root_node; temp_node != NULL && indx != index; temp_node = temp_node->next, indx++);
		return temp_node->data;
	}

	void Clear()
	{
		NODE<T>* temp_node = NULL;
		for (temp_node = this->tail_node; temp_node != NULL;)
		{
			NODE<T>* temp_node2 = temp_node->previous;
			Remove(temp_node);
			temp_node = temp_node2;
		}
	}
};

#endif