#ifndef _NODE_HH_
#define _NODE_HH_
#include <glob.hh>
class node : public std::enable_shared_from_this<node>{
private:
    std::shared_ptr<node>              _parent;
    std::vector<std::shared_ptr<node>> _children;
    uint32_t                           _references;

	 uint32_t									_number_of_mutations;
    std::vector<uint32_t>              _mutations;

    void remove(std::shared_ptr<node>);
    void serialize(std::ofstream&);
    void unserialize(std::ifstream&);

public:
    node(void);
    node(const node&);
    node& operator=(const node&);
    ~node(void);

    void child(std::shared_ptr<node>&);
    void remove(void);
    void parent(std::shared_ptr<node>&);
    void increase(void);
    void number_of_mutations(const uint32_t&);
    void references(const uint32_t&);
    void mutate(const uint32_t&);
    void mutate(void);

    uint32_t references(void) const;
    std::vector<std::shared_ptr<node>>& children(void);
    std::vector<uint32_t>& mutations(void);
    uint32_t number_of_mutations(void) const;
    std::shared_ptr<node>& parent(void);

    json serialize(void);

    void serialize(const std::string&);
    void unserialize(const std::string&);
};
#endif
