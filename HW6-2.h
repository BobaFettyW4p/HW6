// From http://www.cprogramming.com/tutorial/lesson18.html 
// Since we have rewritten this program to utilize unique pointers, we need to include the memory header
#include<memory>

/**
 * This node struct has been rewritten to offer 2 improvements from the original:
 * - It has been templatized, so it can store any type of data, not just ints
 * - It uses std::unique_ptrs instead of raw pointers, which eliminates the need to manually manage memory
 */
template<typename T>
struct node
{
  T key_value;
  // In the given example, the left and right pointers were raw pointers. We are replacing them with std::unique_ptrs instead.
  std::unique_ptr<node<T>> left;
  std::unique_ptr<node<T>> right;
};

/**
 * Similar to the above node struct, this btree class has been rewritten to utilize std::unique_ptrs instead of raw pointers
 * Due to this, we were able to simplify the destructor, and remove the delete_tree() method, instead utilizing RAII to manage memory
 * One major consideration with the switch to unique_ptrs is that a copy constructor does not make sense due to the fact that unique_ptrs cannot be copied
 * However, they can be moved, so I opted not to implement a copy constructor, but to implement a move constructor instead
 * In addition, this class has been templatized, so it can store any type of data, not just ints
 */
template<typename T>
class btree
{
    public:
		// This btree constructor has been changed to initialize root to nullptr instead of NULL
        // This is not a functional change since we do not overload the constructor, but it adheres to best practices
        btree() { 
			root = nullptr;
		}

		// This btree move constructor has been added to initialize root to an existing unique_ptr
		// This constructor is a move constructor (in contrast to a copy constructor) as unique_ptrs cannot be copied
		// This constructor takes ownership of the unique_ptr passed in, and transfers it to the new btree object
		btree(std::unique_ptr<node<T>> new_root) : root(std::move(new_root)) {}

		//Since we rewrote the tree to utilize unique_ptrs instead of raw pointers, the delete_tree() methods have been removed
		//Once the instance of the btree object (and therefore any unique_ptrs) goes out of scope, the memory will be automatically deleted, and this destructor is unnecessary
		// I have left it in the code for clarity, and to give me an opportunity to explain how using unique_ptrs and RAII have simplified object destruction
		~btree() {}

        // The original insert function utilized a private insert() method to perform the node insertion logic, we will retain this functionality
		void insert(T key) {
	// nullptr in the below line replaces NULL
            if (root != nullptr)
				insert(key, root);
			else
			{
				//The below line was originally using operator new to manually allocate memory; I have changed it to use a unique_ptr to allow for modern memory management
                root = std::make_unique<node<T>>();
				root->key_value = key;
                //The below 2 lines utilized NULL instead of nullptr (see lines 22-23 for rationale for this change)
				root->left = nullptr;
				root->right = nullptr;
			}
		}
		// Returns a unique_ptr to the found node (or nullptr if not found)
        // The original search function utilized a private search() method to traverse the tree, we will retain this functionality
		// We have also modified the method to return its value by reference in order to avoid copying the unique_ptr
		const std::unique_ptr<node<T>>& search(T key) {
			static std::unique_ptr<node<T>> null_node = nullptr;
			auto& result = search(key, root);
			return result ? result : null_node;
		}

    private:
		//this method declaration was rewritten to utilize a unique_ptr instead of a raw pointer
        void insert(T key, std::unique_ptr<node<T>>& leaf) {
			if (key < leaf->key_value)
			{
				if (leaf->left != nullptr)
					insert(key, leaf->left);
				//This else block was rewritten to utilize a unique_ptr instead of operator new
                //and NULL was replaced with nullptr
                else
				{
					leaf->left = std::make_unique<node<T>>();
					leaf->left->key_value = key;
					leaf->left->left = nullptr;
					leaf->left->right = nullptr;
				}
			}
			else if (key >= leaf->key_value)
			{
				if (leaf->right != nullptr)
					insert(key, leaf->right);
				//This else block was rewritten to utilize a unique_ptr instead of operator new
                //and NULL was replaced with nullptr
                else
				{
					leaf->right = std::make_unique<node<T>>();
					leaf->right->key_value = key;
					leaf->right->left = nullptr;
					leaf->right->right = nullptr;
				}
			}
		}
		// this implemetation of the private search() method was rewritten to utilize a unique_ptr instead of a raw pointer
		// we are also declaring the method as const as the pointer is not being modified
		// we are also passing the unique_ptr by reference to avoid copying
        const std::unique_ptr<node<T>>& search(T key, const std::unique_ptr<node<T>>& leaf) {
			//the below line was rewritten to refer to nullptr instead of NULL
			if (leaf != nullptr) 
			{
				if (key == leaf->key_value)
					return leaf;
				if (key < leaf->key_value)
					return search(key, leaf->left);
				else
					return search(key, leaf->right);
			}
			else return leaf;
		}

        std::unique_ptr<node<T>> root;
};




