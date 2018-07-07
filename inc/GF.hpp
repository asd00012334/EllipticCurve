#ifndef __GF_HPP__
#define __GF_HPP__

template<typename> class RingPoly;
template<typename> class FieldPoly;
template<typename> class ExtnField;

template<typename Ring>
class RingPoly{
protected:
    Ring const* coefType;
public:
    class Element{
    protected:
        RingPoly const* type;
        vector<Ring::Element> coef;
    public:
        Element operator+=(Element const&);
        Element operator-=(Element const&);
        Element operator*=(Element const&);

        Element operator+(Element const&)const;
        Element operator-(Element const&)const;
        Element operator*(Element const&)const;
        Element& operator=(Element const&);
    };

    RingPoly zero()const;

};

template<typename Field>
class FieldPoly: public RingPoly<Field>{
public:
    class Element: public RingPoly<Field>::Element{
    public:
        Element operator/=(Element const&);
        Element operator%=(Element const&);

        Element operator/(Element const&)const;
        Element operator%(Element const&)const;
        pair<Element,Element> div(Element const&)const;
    };

    FieldPoly one()const;
};

template<typename Field>
class ExtnField{
protected:
    FieldPoly<Field> irr;
public:
    class Element{
    protected:
        ExtnField const* type;
        FieldPoly<Field> val;
    public:
        Element inv()const;

        Element operator+=(Element const&);
        Element operator-=(Element const&);
        Element operator*=(Element const&);
        Element operator/=(Element const&);

        Element operator+(Element const&)const;
        Element operator-(Element const&)const;
        Element operator*(Element const&)const;
        Element operator/(Element const&)const;
        Element& operator=(Element const&);
    };
    ExtnField zero()const;
    ExtnField one()const;

};

template<typename Fq> using GF<Fq> = ExtnField<Fq>;

#endif // __GF_HPP__
