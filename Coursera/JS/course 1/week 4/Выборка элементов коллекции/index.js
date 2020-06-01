/**
 * @param {Array} oldCollection
 * @params {Function[]} – Функции для запроса
 * @returns {Array}
 */
function query(oldCollection) {
    var collection = oldCollection.slice();
    var toBeSelected = [];
    for(let i=1; i<arguments.length; ++i)
    {
        if(arguments[i].name === 'select')
        {
            toBeSelected.push(arguments[i]);
        }
        else if(arguments[i].name === 'filterIn')
        {
            collection = arguments[i](collection);
        }
    }
    // toBeSelected.forEach(function (item) {
    //     collection = item(collection)
    // })
    return toBeSelected.reduce(function (resultCollection, operation) {
        return operation(resultCollection);
    }, collection);
}

/**
 * @params {String[]}
 */
function select() {
    let fields = [].slice.call(arguments);

    return function select(collection) {
        var first = true;
        let selectedFields = {}
        return collection.map(function (item) {
            if (first)
            {
                first = false;
                fields.forEach(function (field) {
                    if(collection[0].hasOwnProperty(field))
                    {
                        selectedFields[field] = true;
                    }
                });
            }
            let selectedItem = {};
            for(let field in selectedFields)
            {
                selectedItem[field] = item[field];
            }
            return selectedItem;
        });
    }
}

/**
 * @param {String} property – Свойство для фильтрации
 * @param {Array} values – Массив разрешённых значений
 */
function filterIn(property, values) {
    return function filterIn(collection) {
        return collection.filter(function (item) {
            return values.includes(item[property]);
            //help
        });
    }
}

module.exports = {
    query: query,
    select: select,
    filterIn: filterIn
};
