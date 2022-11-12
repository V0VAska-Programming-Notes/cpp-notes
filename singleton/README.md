# Singleton.

Редко возникающая, но всё же, тема. Сами разновидности разложены по директориям с приблизительно соответствующими назаваниями, ну а в main.cxx просто тестим готовый результат.

А пока немного теории...

# Классика, так сказать, для однопоточного случая.

```c++
class SingletonBase
{
public:
	static SingletonBase* Get() noexcept
	{
		if (!_instance)
		{
			_instance = new SingletonBase;
		}
		return _instance;
	}
	SingletonBase() {};
	static SingletonBase* _instance;
};

SingletonBase* SingletonBase::_instance = nullptr;
```

# Давим потенциальных тараканов.

## Нахрена доступ извне к статической _instance?

Прячем в private или protected.

## Лазейки в создании объектов синглетона.

Вот уж точно в теле программы нам не нужно ничего (окромя первого оператора) из:

```c++
simple::SingletonBase* obj = simple::SingletonBase::Get();

simple::SingletonBase a;
simple::SingletonBase b = *obj;
simple::SingletonBase c = std::move(*obj);
simple::SingletonBase* obj1 = new simple::SingletonBase;
simple::SingletonBase* obj2;
*obj2 = *obj;
*obj2 = std::move(*obj);
```

Поэтому вспоминаем о [спешиал членах класса](../constructors/special). Достаточно "заделетить" copy конструктор и оператор, тогда и move не создадутся по-умолчанию - ведь "копи" явно определены, и не важно что удалёнными.

```c++
	SingletonBase(const SingletonBase&) = delete;
	SingletonBase& operator= (const SingletonBase&) = delete;
```

С учётом всего наш подопытный приобретает следующий вид:

```c++
class SingletonBase
{
public:
	static SingletonBase* Get() noexcept
	{
		if (!_instance)
		{
			_instance = new SingletonBase;
		}
		return _instance;
	}

	SingletonBase(const SingletonBase&) = delete;
	SingletonBase& operator= (const SingletonBase&) = delete;
protected:
	SingletonBase() = default;
private:
	static SingletonBase* _instance;
};

SingletonBase* SingletonBase::_instance = nullptr;
```

# Итого

- слегка переделанный наш ["простецкий"](simple) синглетон.
- несколько забавный ["безуказательный"](pointerless) вариант, именуемый как Meyers Singleton. Пожалуй, один из самых быстрых в **многопоточной** среде. Использует фишку, что статическая переменная в блоке создаётся **единожды**
- [classic](classic) - само название за себя говорит.
