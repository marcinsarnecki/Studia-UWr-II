const list = document.getElementById('poke_list'); // list of pokemons
const pokeInfo = document.getElementById('poke_info'); // div to print pokemon info

/**
 * Function to make pop up information about error
 * @param {*} err 
 */
const handleError = (err) => {
    window.alert(err);
}

/**
 * Function to get pokemon's flavor (first in english) and save it
 * @param {string} url - url to pokemon's species api
 * @param {*} textNode - node to save flavor
 */
const getFlavor = (url, textNode) => {
    fetch(url)
    .then((res) => res.json())
    .then((data) => {
        let found = false;
        data.flavor_text_entries.filter(entry => {
            if(entry.language.name == 'en' && !found) {
                found = true;
                textNode.nodeValue = entry.flavor_text;
            }
            
        })
    }).catch((err) => handleError(err));
}

/**
 * Function to render pokemon on the page
 * @param {*} data - pokemon's data from api
 */
const createPokemon = (data) => {
    pokeInfo.innerHTML = ''; //clear pokemon info

    let pokeInfoHeader = document.createElement('h3'); //pokemon name as header
    let name = data.name;
    let textNode = document.createTextNode(data.name.toUpperCase());
    pokeInfoHeader.appendChild(textNode);
    pokeInfo.appendChild(pokeInfoHeader);


    let pokeInfoImage = document.createElement('img'); //image
    pokeInfoImage.setAttribute('src', data.sprites.front_default);
    pokeInfo.appendChild(pokeInfoImage);

    let pokeInfoTypes = document.createElement('div'); //types of pokemon as inline paragraphs in div
    let types = data.types;
    types.map(type => {
        let p = document.createElement('p');
        p.classList.add('poke_type');
        let text = document.createTextNode(type.type.name);
        p.appendChild(text);
        pokeInfoTypes.appendChild(p);
    })
    pokeInfo.appendChild(pokeInfoTypes);

    let pokeInfoDescription = document.createElement('p'); //description as paragraph
    pokeInfoDescription.classList.add('poke_description')
    let textNode2 = document.createTextNode('');
    getFlavor(data.species.url, textNode2);
    pokeInfoDescription.appendChild(textNode2);
    pokeInfo.appendChild(pokeInfoDescription);
}


/**
 * Function to get pokemon data and render it after click
 * @param {string} url - url to pokemon's api
 */
const getPokemon = (url) => {
    fetch(url)
    .then((res) => res.json())
    .then((data) => createPokemon(data))
    .catch((err) => handleError(err));
}


/**
 * Function to generate pokemons list
 * @param {*} data - pokemons from api
 */
const createNavList = (data) => {
    const pokemons = data.results;
    pokemons.map(pokemon => {
        let element = document.createElement('li');
        let link = document.createElement('a');
        let name = document.createTextNode(pokemon.name.toUpperCase());
        link.appendChild(name);
        link.setAttribute('href', '#');
        link.setAttribute('onclick', `getPokemon("${pokemon.url}")`);
        element.appendChild(link);
        list.appendChild(element);
    })
}

fetch("https://pokeapi.co/api/v2/pokemon?limit=151")
.then((res) => res.json())
.then((data) => createNavList(data))
.catch((err) => handleError(err));