#include <simulator.hh>
namespace haploid{
Simulator::Simulator(void)
{
    this->_popset=nullptr;
    this->_evlist=nullptr;
}
Simulator::Simulator(const json &_fsettings)
{
    this->_popset=std::make_shared<popset>(_fsettings["individual"]);
    this->_evlist=std::make_shared<evlist>(_fsettings["scenario"]);
}
Simulator::Simulator(const Simulator &_simulator)
{
    this->_popset=std::make_shared<popset>(*_simulator._popset);
    this->_evlist=std::make_shared<evlist>(*_simulator._evlist);
}
Simulator& Simulator::operator=(const Simulator &_simulator)
{
    this->_popset=std::make_shared<popset>(*_simulator._popset);
    this->_evlist=std::make_shared<evlist>(*_simulator._evlist);
    return(*this);
}
Simulator::~Simulator(void)
{

}
void Simulator::run(const std::string &_directory)
{
    uint32_t lvt=0U;

    while(!this->_evlist->empty())
        {
            std::shared_ptr<event> e=this->_evlist->top();

            for(; lvt<e->timestamp(); ++lvt)
                {
                    this->_popset->drift();
                    if(!last(e)) this->_popset->flush();
                }

            switch(e->type())
                {
                case CREATE:
                {
                    this->_popset->create(e->params());
                    break;
                }
                case INCREMENT:
                {
                    this->_popset->increment(e->params());
                    break;
                }
                case DECREMENT:
                {
                    this->_popset->decrement(e->params());
                    break;
                }
                case SPLIT:
                {
                    this->_popset->split(e->params());
                    break;
                }
                case ENDSIM:
                {
                    this->_popset->mutate();
                    break;
                }
                default:
                {
                    std::cerr << "unknown event " << e->type() << std::endl;
                    exit(EXIT_FAILURE);
                }

                }
            this->_evlist->pop();
        }
    this->_popset->stats(_directory);
    this->_popset->save(_directory);
}
};
