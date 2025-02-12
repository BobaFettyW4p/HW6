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

template<typename T>
class btree
{
    public:
		// This btree constructor has been changed to initialize root to nullptr instead of NULL
        // This is not a functional change since we do not overload the constructor, but it adheres to best practices
        btree() { 
			root = nullptr;
		}
		~btree() {
			destroy_tree();
		}
        // The original insert function utilized a private insert() method to perform the node insertion logic, we will retain this functionality
		void insert(T key) {
			// nullptr in the below line replaces NULL, for the reasons listed on lines 22-23
            if (root != nullptr)
				insert(key, root);
			else
			{
				//The below line was originally using operator new to manually allocate memory; I have upgraded it to use a unique_ptr to allow for modern memory management
                root = std::make_unique<node<T>>();
				root->key_value = key;
                //The below 2 lines utilized NULL instead of nullptr (see lines 22-23 for rationale for this change)
				root->left = nullptr;
				root->right = nullptr;
			}
		}
		// Returns a unique_ptr to the found node (or nullptr if not found)
        // The original search function utilized a private search() method to traverse the tree, we will retain this functionality
		std::unique_ptr<node<T>> search(T key) {
			return search(key, root);
		}
		void destroy_tree() {
			destroy_tree(root);
		}

    private:
		//This function was rewritten to utilize a unique_ptr instead of a raw pointer
        //In addition to following best practices, this allows us to automatically delete the node when the unique_ptr is reset
        void destroy_tree(std::unique_ptr<node<T>>& leaf) {
			if (leaf) { 
				destroy_tree(leaf->left);
				destroy_tree(leaf->right);
			}
		}
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
		//This method declaration was rewritten to utilize a unique_ptr instead of a raw pointer
        std::unique_ptr<node<T>>& search(T key, std::unique_ptr<node<T>>& leaf) {
			if (leaf)
			{
				if (key == leaf->key_value)
					return leaf;
				if (key<leaf->key_value)
					return search(key, leaf->left);
				else
					return search(key, leaf->right);
			}
			//if the key is not found, return a nullptr
            return std::unique_ptr<node<T>>();
		}

        std::unique_ptr<node<T>> root;
};




