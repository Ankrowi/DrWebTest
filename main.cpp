#include <iostream>
#include <map>

template<class Key>
class not_found_exception : public std::exception
{
public:
    virtual const Key& get_key() const noexcept = 0;
};

template<class Key>
class key_not_found : public not_found_exception<Key>
{
public:
    explicit key_not_found(const Key& key) noexcept;
    ~key_not_found() noexcept override = default;
    virtual const Key& get_key() const noexcept;
private:
    Key key;
};

template<class Key>
key_not_found<Key>::key_not_found(const Key& key) noexcept
{
    this->key = key;
}

template<class Key>
const Key& key_not_found<Key>::get_key() const noexcept
{
    return key;
}


template<class Key, class Value>
class dictionary
{
public:
    virtual ~dictionary() = default;
    virtual const Value& get(const Key& key) const = 0;
    virtual void set(const Key& key, const Value& value) = 0;
    virtual bool is_set(const Key& key) const = 0;
};

template<class Key, class Value>
class my_dictionary : public dictionary<Key, Value>
{
public:
    my_dictionary() = default;
    virtual const Value& get(const Key& key) const;
    virtual void set(const Key& key, const Value& value);
    virtual bool is_set(const Key& key) const;
private:
    std::map<Key, Value> _dictionary;
};

template<class Key, class Value>
const Value& my_dictionary<Key, Value>::get(const Key& key) const
{
    if (is_set(key)) {
        return _dictionary.at(key);
    }
    else {
        throw key_not_found<Key>(key);
    }
}

template<class Key, class Value>
void my_dictionary<Key, Value>::set(const Key& key, const Value& value)
{
    _dictionary[key] = value;
}

template<class Key, class Value>
bool my_dictionary<Key, Value>::is_set(const Key& key) const
{
    return _dictionary.find(key) != _dictionary.end();
}

int main()
{
    my_dictionary<int, int> md;
    try {
        md.set(1, 10);
        std::cout << md.get(2);
    }
    catch(key_not_found<int> exc) {
        std::cout << exc.what() << " " << exc.get_key();
    }
    
}


