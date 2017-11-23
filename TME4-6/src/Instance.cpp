#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Cell.h"
#include "Term.h"
#include "Point.h"

using namespace Netlist;

Instance::Instance (Cell* owner, Cell* model, const std::string& s) :
	owner_(owner),
	masterCell_(model),
	name_(s),
	terms_(),
	position_()
{
	for (std::vector<Term*>::const_iterator it = model->getTerms().begin();
			it != model->getTerms().end();
			it++)
	{
		new Term(this, *it);
	}
	owner_->add(this);
}

Instance::~Instance ()
{
	for (std::vector<Term*>::iterator it = terms_.begin();
			it != terms_.end();
			it++)
	{
		delete *it;
	}
	owner_->remove(this);
}

Term* Instance::getFromTerms ( const std::string& name ) const
{
	for ( std::vector<Term*>::const_iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm ) {
	  if ((*iterm)->getName() == name)  return *iterm;
	}
	return NULL;
}

bool Instance::connect (const std::string& name, Net* n)
{
    Term* term = getFromTerms(name);
    if (term == NULL) return false;
 
    term->setNet(n);
    return true;
}

void Instance::add(Term* t)
{
	terms_.push_back(t);
}

void Instance::remove (Term* t)
{
    for ( std::vector<Term*>::iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm ) {
      if (*iterm == t) terms_.erase( iterm );
	}
}

void Instance::setPosition (const Point& p)
{
	position_ = p;
}

void Instance::setPosition (int x, int y)
{
	position_ = Point (x, y);
}

void Instance::toXml(std::ostream& o)
{
	o << indent << "<instance name=\"" << name_ << "\"";
	o << " mastercell=\"" << masterCell_->getName() << "\"";
	o << " x=\"" << position_.getX();
	o << " y=\"" << position_.getY();
	o << "/>" << std::endl;
}