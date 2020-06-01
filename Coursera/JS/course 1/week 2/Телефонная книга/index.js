// Телефонная книга
var phoneBook = {};
var nameByPhone = {};

function Add(name, tels)
{
    tels=tels.split(',').reduce(function (acc, elem) {
        acc[elem] = true;
        return acc;
    }, {});

    for(let tel in tels)
    {
        Remove(tel);
    }
    for(let tel in tels)
    {
        if(!phoneBook.hasOwnProperty(name))
        {
            phoneBook[name] = [];
        }
        ////////// ??????????????????????????????????????????
        phoneBook[name].push(tel);
        nameByPhone[tel] = name;
    }
    // console.log(phoneBook);
    // console.log(nameByPhone);
}

function Show()
{
    var result = [];
    var names = Object.keys(phoneBook).sort();
    for(var i=0; i<names.length; ++i)
    {
        var name = names[i];
        // console.log(name);
        // console.log(Object.keys(phoneBook[name]))
        if(phoneBook[name].length>0)
        {
            result.push(name + ': ' + phoneBook[name].join(', '));
        }
    }
    // console.log(result);
    return result;
}

function Remove(tel)
{

    if(!nameByPhone.hasOwnProperty(tel))
    {
        return false;
    }

    var name = nameByPhone[tel];
    let nameIdx;
    for(let i=0; i<phoneBook[name].length; ++i)
    {
        if(phoneBook[name][i] === tel)
        {
            nameIdx = i;
            break;
        }
    }

    delete nameByPhone[tel];
    phoneBook[name].splice(nameIdx, 1);
    if(phoneBook[name].length === 0)
    {
        delete phoneBook[name]
    }

    return true;
}

/**
 * @param {String} command
 * @returns {*} - результат зависит от команды
 */
module.exports = function (command) {
    var params = command.split(' ');
    switch (params[0]) {
        case 'ADD':
            return Add(params[1], params[2]);
        case 'REMOVE_PHONE':
            return Remove(params[1]);
        case 'SHOW':
            return Show();
    }
};
