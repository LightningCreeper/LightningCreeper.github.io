function changeheader(id, id2) {
    var element = document.getElementsById(id);
    var element2 = document.getElementsById(id2);
    if (element.style.height == '200px') {
        element.style.height = '50px';
        element2.style.padding = '50px 0px 0px 50px';
    } else {
        element.style.height = '200px';
        element2.style.padding = '200px 0px 0px 50px';
    }
}