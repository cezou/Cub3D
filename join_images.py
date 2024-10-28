import os
from gimpfu import *

def join_images_horizontally(image, drawable, folder_path):
    # Get all image file names in the folder
    image_files = [f for f in os.listdir(folder_path) if f.endswith(('.png', '.jpg', '.jpeg'))]
    
    if not image_files:
        pdb.gimp_message("No images found in the folder.")
        return

    images = []
    total_width = 0
    max_height = 0

    # Open each image and calculate dimensions
    for image_file in image_files:
        img = pdb.gimp_file_load(os.path.join(folder_path, image_file), image_file)
        images.append(img)
        total_width += img.width
        max_height = max(max_height, img.height)

    # Create a new image with combined width and max height
    new_image = pdb.gimp_image_new(total_width, max_height, RGB)
    x_offset = 0

    # Copy each image into the new image
    for img in images:
        layer = pdb.gimp_layer_new_from_visible(img, new_image, img.name)
        pdb.gimp_image_insert_layer(new_image, layer, None, -1)
        pdb.gimp_layer_set_offsets(layer, x_offset, 0)
        x_offset += img.width
        pdb.gimp_image_delete(img)  # Close original images to free memory

    # Show the result
    pdb.gimp_display_new(new_image)

# Register the function in GIMP
register(
    "python_fu_join_images_horizontally",
    "Join Images Horizontally",
    "Joins all images in a folder horizontally into a single image.",
    "Your Name", "Your Name", "2023",
    "<Image>/Filters/Combine/Join Images Horizontally...",
    "*",  # This script doesn't require an existing image open
    [
        (PF_DIRNAME, "folder_path", "Folder containing images", None)
    ],
    [],
    join_images_horizontally
)

main()