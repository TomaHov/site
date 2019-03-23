#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cstddef> 
#include <stdexcept> 
#include <iostream>
#include <stack>

using namespace std;

class BinaryTree
{
	struct Node
	{
		int data;
		Node *left;
		Node *right;

		Node(Node *l, int d, Node *r)
			: data(d)
			, left(l)
			, right(r)
		{}
	};

	void remove_child(Node *parent, char child_position)
	{
		Node *child = nullptr;
		Node *new_child = nullptr;
		//git

		if (child_position == 'l')
		{
			child = parent->left;
			if (child->left != nullptr)
			{
				new_child = child->left;
				if (child->right != nullptr)
				{
					Node *iter = child->left;
					while (true)
					{
						if (iter->right == nullptr)
							break;
						iter = iter->right;
					}
					iter->right = child->right;
				}
			}
			else if (child->right != nullptr)
			{
				new_child = child->right;
				if (child->left != nullptr)
				{
					Node *iter = child->right;
					while (true)
					{
						if (iter->left == nullptr)
							break;
						iter = iter->left;
					}
					iter->left = child->left;
				}
			}
			parent->left = new_child;
		}
		else
		{
			child = parent->right;
			if (child->left != nullptr)
			{
				new_child = child->left;
				if (child->right != nullptr)
				{
					Node *iter = child->left;
					while (true)
					{
						if (iter->right == nullptr)
							break;
						iter = iter->right;
					}
					iter->right = child->right;
				}
			}
			else if (child->right != nullptr)
			{
				new_child = child->right;
				if (child->left != nullptr)
				{
					Node *iter = child->right;
					while (true)
					{
						if (iter->left == nullptr)
							break;
						iter = iter->left;
					}
					iter->left = child->left;
				}
			}
			parent->right = new_child;
		}
		delete child;
	}

	void print_help(const Node *node) const
	{
		if (node != nullptr)
		{
			print_help(node->left);
			std::cout << node->data << " ";
			print_help(node->right);
		}
	}

public:
	BinaryTree()
		: size_(0)
		, root_(nullptr)
	{}

	void insert(int element)
	{
		if (size_ == 0)
		{
			root_ = new Node(nullptr, element, nullptr);
		}
		else
		{
			Node *iter = root_;
			while (true)
			{
				if (element < iter->data)
				{
					if (iter->left == nullptr)
					{
						iter->left = new Node(nullptr, element, nullptr);
						break;
					}
					iter = iter->left;
				}
				else
				{
					if (iter->right == nullptr)
					{
						iter->right = new Node(nullptr, element, nullptr);
						break;
					}
					iter = iter->right;
				}
			}
		}
		++size_;
	}

	bool erase(int element)
	{
		if (size_ == 0)
			return false;

		if (element == root_->data)
		{
			Node *new_root = nullptr;
			
			if (root_->left != nullptr)
			{
				new_root = root_->left;
				if (root_->right != nullptr)
				{
					Node *iter = root_->left;
					while (true)
					{
						if (iter->right == nullptr)
							break;
						iter = iter->right;
					}
					iter->right = root_->right;
				}
			}
			else if (root_->right != nullptr)
			{
				new_root = root_->right;
				if (root_->left != nullptr)
				{
					Node *iter = root_->right;
					while (true)
					{
						if (iter->left == nullptr)
							break;
						iter = iter->left;
					}
					iter->left = root_->left;
				}
			}

			delete root_;
			root_ = new_root;
		}
		else
		{
			Node *iter = root_;
			while (true)
			{
				if (iter->left != nullptr && iter->left->data == element)
				{
					remove_child(iter, 'l');
					break;
				}

				if (iter->right != nullptr && iter->right->data == element)
				{
					remove_child(iter, 'r');
					break;
				}

				if (element < iter->data)
				{
					if (iter->left == nullptr)
						return false;
					iter = iter->left;
				}
				else
				{
					if (iter->right == nullptr)
						return false;
					iter = iter->right;
				}
			}
		}

		--size_;
		return true;
	}

	int get_min() const
	{
		if (size_ == 0)
			throw std::logic_error("call get_min method when tree is empty");
		Node *iter = root_;
		while (iter->left != nullptr)
			iter = iter->left;
		return iter->data;
	}

	int get_max() const
	{
		if (size_ == 0)
			throw std::logic_error("call get_max method when tree is empty");
		Node *iter = root_;
		while (iter->right != nullptr)
			iter = iter->right;
		return iter->data;
	}

	void print() const
	{
		if (size_ != 0)
		{
			print_help(root_);
			std::cout << std::endl;
		}
	}

	size_t size() const
	{
		return size_;
	}

private:
	size_t size_;
	Node *root_;
};


int main()
{
	srand(time(nullptr));

	BinaryTree tree;
	tree.insert(50);
	for (int i = 0; i < 9; ++i)
		tree.insert(rand() % 100);

	tree.print();
	cout << "size is " << tree.size() << endl;
	cout << "min is " << tree.get_min() << endl;
	cout << "max is " << tree.get_max() << endl << endl;

	cout << "erase(50)" << endl;
	cout << "erase(min)" << endl;
	cout << "erase(max)" << endl << endl;
	tree.erase(50);
	tree.erase(tree.get_min());
	tree.erase(tree.get_max());

	tree.print();
	cout << "size is " << tree.size() << endl << endl;

	return 0;
}