package map.lab7.repository.file;


import map.lab7.domain.Entity;
import map.lab7.repository.memory.InMemoryRepository;

import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;


public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID,E> {
    String fileName;

    /**
     *
     * @param fileName
     */
    public AbstractFileRepository(String fileName) {
        this.fileName = fileName;
        loadData();

    }

    /**
     *
     */
    private void loadData() { //decorator pattern
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String newLine;
            while ((newLine = reader.readLine()) != null) {
                //System.out.println(newLine);
                List<String> data = Arrays.asList(newLine.split(";"));
                E entity = extractEntity(data);
                super.add(entity);
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
//        Path path= Paths.get(fileName);
//        try{
//            List<String> lines= Files.readAllLines(path);
//            lines.forEach(line -> {
//                E entity=extractEntity(Arrays.asList(line.split(";")));
//                super.save(entity);
//            });
//        }
//        catch (IOException e){
//            e.printStackTrace();
//        }

    }

    /**
     * extract entity  - template method design pattern
     * creates an entity of type E having a specified list of @code attributes
     *
     * @param attributes
     * @return an entity of type E
     */
    public abstract E extractEntity(List<String> attributes);  //Template Method


    /**
     *
     * @param entity
     * @return
     */
    protected abstract String createEntityAsString(E entity); //Template Method

    /**
     *
     * @param entity
     *         entity must be not null
     * @return
     */
    @Override
    public Optional<E> add(E entity) {
        Optional<E> result = super.add(entity);
        if (result.isEmpty())
            writeToFile(entity);
        return result;

    }

    /**
     *
     * @param entity
     */
    protected void writeToFile(E entity) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true))) {

            writer.write(createEntityAsString(entity));
            writer.newLine();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
