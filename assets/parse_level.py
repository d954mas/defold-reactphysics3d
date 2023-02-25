import deftree
import json

locations = ["castle_scene"]
ignore_containers = []
valid_containers_by_zone = {
    "Collection" : [],
}
print("start")
for l in locations:
    print("LOCATION:" + l + "*******************")
    tree = deftree.parse("..\\" + l + "\\" + "Collection.collection")  
    root = tree.get_root()

    level_containers = []
    objects_by_container = {}
    buildings = []
    print("find_____")
    valid_containers = False
    for child in root.iter_elements("embedded_instances"):
        if(child.get_attribute("id") == "__root"):
            for attr in child.iter_attributes("children"):
                if attr.value not in ignore_containers:
                    if not valid_containers or attr.value in valid_containers:
                        level_containers.append(attr.value)
                        objects_by_container[attr.value] = []
                        print("" + attr.value)

    print("fill_____")
    for child in root.iter_elements("embedded_instances"):
        container_id = child.get_attribute("id").value
        if(container_id in level_containers):
             array = objects_by_container[container_id]
             print("" + container_id)
             for attr in child.iter_attributes("children"):
                  array.append(attr.value)
        if(container_id == "blender"):
            for attr in child.iter_attributes("children"):
                buildings.append(attr.value)



    def_elem_by_id = {}
    for child in root.iter_elements("instances"):
        id = child.get_attribute("id").value
        def_elem_by_id[id] = child

    print("prepare result_____")
    result = {
     
        }
    for key, value in objects_by_container.items():
        print(key+ "_______________________________")
        result_array = []
        result[key]=result_array;
        for child_id in value:
            child = def_elem_by_id[child_id]
        #    print(child_id)
            if child is None:  raise Exception("No child:" + child_id)
            prototype = child.get_attribute("prototype").value
            prototype =  prototype[prototype.rindex('/')+1:]

            result_child = {
                "id":child_id,
                "prototype":prototype
                }
            result_array.append(result_child)

    with open('./custom_resources/' + l  + '/' + 'level_objects.json', 'w') as f:
        json.dump(result, f)

