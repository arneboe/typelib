#ifndef __TYPESOLVER_H__
#define __TYPESOLVER_H__

#include "CPPParser.hh"

#include "typemodel.hh"
#include "typebuilder.hh"
#include <list>
#include <sstream>

namespace Typelib { class Registry; }
   
class TypeSolver : public CPPParser
{
    bool            m_class;
    std::string     m_class_name;
    TypeSpecifier   m_class_type;

    // For Compound
    typedef std::pair<std::string, Typelib::TypeBuilder> FieldBuilder;
    typedef std::list< FieldBuilder > FieldList;
    std::list<std::string> m_fieldtype;
    FieldList       m_fields;

    // For Enums
    typedef std::list< std::pair<std::string, int> > ValueMap;
    ValueMap        m_enum_values;

    void buildClassObject(bool define_type);
    Typelib::Registry& m_registry;

public:
    class UnsupportedClassType
    {
        int m_type;
    public:
        UnsupportedClassType(int type) : m_type(type) {}
        std::string toString() 
        { 
            std::ostringstream stream;
            stream << "unsupported class type " << m_type; 
            return stream.str();
        }
    };
    
    TypeSolver(antlr::TokenStream& lexer, Typelib::Registry& registry);
    TypeSolver(const antlr::ParserSharedInputState& state, Typelib::Registry& registry);
    
    virtual void beginClassDefinition(TypeSpecifier class_type, const std::string& name);
    virtual void endClassDefinition();
    virtual void beginEnumDefinition(const std::string& name);
    virtual void enumElement(const std::string& name, bool has_value, int value);
    virtual void endEnumDefinition();

    virtual void beginFieldDeclaration();
    virtual void foundSimpleType(const std::list<std::string>& full_type);
    virtual void classForwardDeclaration(TypeSpecifier ts, DeclSpecifier,const std::string& name);
    virtual void end_of_stmt();
    virtual void declaratorID(const std::string& name, QualifiedItem);
    virtual void declaratorArray(int size);
};

#endif
